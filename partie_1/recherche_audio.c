#include <inttypes.h>
#include <math.h>
#include "recherche_audio.h"
#include "constantes.h"

/**
 * Structure représentant une fenetre de descripteur
 */
typedef struct _window {
    sds* values;
    int count_values;
} Window;


// RESULTATS

/**
 * Ajoute un resultat recusrsivement a la liste chainee de resultats
 * 
 * @param  results     Pointeur vers la premiere entree de la liste de resultats
 * @param  filename    Nom du fichier du resultat
 * @param  match_time  Temps d'apparition du resultat
 * @param  score       Score du resultat
 */
void add_result(RESULT_RECHERCHE_AUDIO** results, const sds filename, const float match_time, const int score) {
    if(*results == NULL) {
        *results = (RESULT_RECHERCHE_AUDIO*) malloc(sizeof(RESULT_RECHERCHE_AUDIO));
        (*results)->filename = filename;
        (*results)->match_time = match_time;
        (*results)->score = score;
        (*results)->next = NULL;
    } else add_result(&(*results)->next, filename, match_time, score);
}

/**
 * Libere recursivement la chaine de resultats de recherche
 * 
 * @param  results  Liste chainee de resultats
 */
void free_results_audio(RESULT_RECHERCHE_AUDIO* results) {
    if(results == NULL)
        return;
    if(results->next != NULL)
        free_results_audio(results->next);
    sdsfree(results->filename);
    free(results);
}


// RECHERCHE

/**
 * Calcule le nombre d'iterations de la boucle de distance
 * (evaluation progressive des fenetres du fichier "jingle" avec
 * les fenetres du fichier "corpus")
 * 
 * @param  count_corpus_lines  Nombre de fenetres du fichier "corpus"
 * @param  count_jingle_lines  Nombre de fenetres du fichier "jingle"
 * @param  window_step         Nombre de fenetres de decalage a chaque iteration de la boucle de distance
 * @return Nombre d'iteration de la boucle de distance
 */
int distance_loop_iterations(const int count_corpus_lines, const int count_jingle_lines, const int window_step) {
    return (int) floor((((float)count_corpus_lines)/window_step)-(((float)count_jingle_lines)/window_step)+1);
}

/**
 * Calcule le temps en seconde correspondant a une iteration de la boucle de distance
 * 
 * @param  dist_loop_iteration  Numero d'iteration de la boucle de distance
 * @param  count_corpus_lines   Nombre de fenetres du fichier "corpus"
 * @param  count_jingle_lines   Nombre de fenetres du fichier "jingle"
 * @param  nb_sample_window     Nombre d'echantillons par fenetre
 * @param  window_step          Nombre de fenetres de decalage a cahque iteration de la boucle de distance
 * @return Temps en seconde correspondant a l'iteration de la boucle de distance
 */
float match_time(const int dist_loop_iteration, const int count_corpus_lines, const int count_jingle_lines, const int nb_sample_window, const int window_step) {
    return (float)dist_loop_iteration*count_corpus_lines/distance_loop_iterations(count_corpus_lines, count_jingle_lines, window_step)/(16000/nb_sample_window);
}

/**
 * Calcul de distance entre deux fenetres de descripteurs
 * 
 * @param  fenetre_corpus     Fenetre du fichier "corpus"
 * @param  fenetre_jingle     Fenetre du fichier "jingle"
 * @param  nb_intervalle_amp  Nombre d'intervalles d'amplitude par fenetre
 * @return Distance antre les deux fenetres
 */
int distance(const sds* fenetre_corpus, const sds* fenetre_jingle, const int nb_intervalle_amp) {
    unsigned int dist = 0;
    for(int i = 0; i < nb_intervalle_amp; i++) {
        char* endptr;
        dist += abs(strtoimax(fenetre_corpus[i], &endptr, 10) - strtoimax(fenetre_jingle[i], &endptr, 10));
    }
    return dist;
}

/**
 * Compare un fichier "jingle" avec les fichiers "corpus" de la base de 
 * descripteurs et permet d'identifier les temps d'apparition
 *
 * @param  chemin_fichier    Chemin vers le fichier "jingle"
 * @param  desc_base         Descripteurs de la base
 * @param  window_step       Nombre de fenetres entre chaque calcul de distance sur les descripteurs de la base
 * @param  nb_sample_window  Nombre d'echantillons par fenetre (parametre d'indexation)
 * @param  nb_intervale_amp  Nombre d'intervalles d'amplitude par fenetre (parametre d'indexation)
 * 
 * @return Liste chainee des resultats (a liberer avec free_results_audio(.))
 */
RESULT_RECHERCHE_AUDIO* recherche_audio(const sds chemin_fichier, const Capsule desc_base, const int window_step, const int nb_sample_window, const int nb_intervalle_amp) {
    RESULT_RECHERCHE_AUDIO* resultats = NULL;
    
    // Recuperation du descripteur du fichier "jingle"
    sds desc_jingle = indexation_audio(chemin_fichier, nb_sample_window, nb_intervalle_amp); // OPTION: NO REINDEX -> FETCH INDEX IN DB

    if(sdslen(desc_jingle) == 0)
        return resultats;

    // Separation des fenetres du descripteur "jingle"
    int count_desc_lines = 0;
    sds* desc_jingle_lines = sdssplitlen(desc_jingle, sdslen(desc_jingle), "]", 1, &count_desc_lines);

    // Separation des fenetres des descripteurs de la base ("corpus")
    int* count_base_descs_lines = (int*) malloc(sizeof(int)*nombreDescripteurs(desc_base));
    sds** base_descs_lines = (sds**) malloc(sizeof(sds*)*nombreDescripteurs(desc_base));
    sds* filenames = (sds*) malloc(sizeof(sds) * nombreDescripteurs(desc_base));
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        filenames[i] = sdsnewlen("",50);
        sscanf(desc_base.descripteurs[i], "%[^;]", filenames[i]);
        sdsupdatelen(filenames[i]);

        sds filename = sdsdup(filenames[i]);
        filename = sdscat(filename, ";");
        sdstrim(desc_base.descripteurs[i], filename);
        base_descs_lines[i] = sdssplitlen(desc_base.descripteurs[i], sdslen(desc_base.descripteurs[i]), "]", 1, &count_base_descs_lines[i]);
        sdsfree(filename);
    }
    
    // Separation des valeurs des echantillons du fichier "jingle"
    Window* windows_j = (Window*) malloc(sizeof(Window)*count_desc_lines);
    for(int i = 0; i < count_desc_lines; i++) {
        sdstrim(desc_jingle_lines[i], "[");
        windows_j[i].values = sdssplitlen(desc_jingle_lines[i], sdslen(desc_jingle_lines[i]), " ", 1, &windows_j[i].count_values);
    }

    // Separation des valeurs des echantillons des fichiers de la base
    Window** windows_c = (Window**) malloc(sizeof(Window*)*nombreDescripteurs(desc_base));
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        windows_c[i] = (Window*) malloc(sizeof(Window)*count_base_descs_lines[i]);
        for(int j = 0; j < count_base_descs_lines[i]; j++) {
            sdstrim(base_descs_lines[i][j], "[");
            windows_c[i][j].values = sdssplitlen(base_descs_lines[i][j], sdslen(base_descs_lines[i][j]), " ", 1, &windows_c[i][j].count_values);
        }
    }
    
    // Tableau de recuperation des evaluations de distance
    int** distances = (int**) malloc(sizeof(int*) * nombreDescripteurs(desc_base));
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        int a = distance_loop_iterations(count_base_descs_lines[i], count_desc_lines, window_step);
        distances[i] = (int*) malloc(sizeof(int*) * a);
        for(int j = 0; j < a; j++)
            distances[i][j] = 0;
    }

    // Comparaison
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        // Pour chaque fenetre du "corpus" sur *window_step* : evalue la distance avec la fenetre du "jingle"
        for(int j = 0, jj = 0; j < count_base_descs_lines[i]-1 && j <= count_base_descs_lines[i]-count_desc_lines; j+=window_step, jj++) {
            for(int k = 0; k < count_desc_lines-1; k++)
                // Calcul de distance entre les fenetres
                distances[i][jj] += distance(windows_c[i][j+k].values, windows_j[k].values, nb_intervalle_amp);
        }
    }

    // Resultats
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        int a = distance_loop_iterations(count_base_descs_lines[i], count_desc_lines, window_step);
        for(int j = 0; j < a; j++)
            if(distances[i][j] < 5000) {
                float matched_time = match_time(j, count_base_descs_lines[i], count_desc_lines, nb_sample_window, window_step);
                add_result(&resultats, sdsdup(filenames[i]), matched_time, distances[i][j]);
            }
    }

    // Liberation memoire allouee
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        free(distances[i]);
    }
    free(distances);
    for(int i = 0; i < nombreDescripteurs(desc_base); i++) {
        for(int j = 0; j < count_base_descs_lines[i]; j++)
            sdsfreesplitres(windows_c[i][j].values, windows_c[i][j].count_values);
        free(windows_c[i]);
    }
    free(windows_c);
    for(int i = 0; i < nombreDescripteurs(desc_base); i++)
        sdsfreesplitres(base_descs_lines[i], count_base_descs_lines[i]);
    free(base_descs_lines);
    free(count_base_descs_lines);
    for(int i = 0; i < count_desc_lines; i++)
        sdsfreesplitres(windows_j[i].values, windows_j[i].count_values);
    free(windows_j);
    sdsfreesplitres(desc_jingle_lines, count_desc_lines);
    for(int i = 0; i < nombreDescripteurs(desc_base); i++)
        sdsfree(filenames[i]);
    free(filenames);
    sdsfree(desc_jingle);

    // Retour
    return resultats;
}