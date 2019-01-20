app.out: main.o indexation.o indexation_texte.o indexation_image.o indexation_audio.o recherche.o recherche_texte.o recherche_image.o recherche_audio.o
	@gcc -o app.out main.o indexation.o indexation_texte.o indexation_image.o indexation_audio.o recherche.o recherche_texte.o recherche_image.o recherche_audio.o
	
main.o: main.c indexation.h recherche.h constantes.h
	@gcc -c main.c

indexation.o: indexation.c indexation.h indexation_texte.h indexation_image.h indexation_audio.h constantes.h
	@gcc -c indexation.c

indexation_texte.o: indexation_texte.c indexation_texte.h constantes.h
	@gcc -c indexation_texte.c

indexation_image.o: indexation_image.c indexation_image.h constantes.h
	@gcc -c indexation_image.c

indexation_audio.o: indexation_audio.c indexation_audio.h constantes.h
	@gcc -c indexation_audio.c

recherche.o: recherche.c recherche.h recherche_texte.h recherche_image.h recherche_audio.h constantes.h
	@gcc -c recherche.c

recherche_texte.o: recherche_texte.c recherche_texte.h indexation_texte.h constantes.h
	@gcc -c recherche_texte.c

recherche_image.o: recherche_image.c recherche_image.h indexation_image.h constantes.h
	@gcc -c recherche_image.c

recherche_audio.o: recherche_audio.c recherche_audio.h indexation_audio.h constantes.h
	@gcc -c recherche_audio.c
	
sds.o: sds.c sds.h sdsalloc.h
	@gcc -c sds.c
	
sauvegarde_descripteurs.o: sauvegarde_descripteurs.c sauvegarde_descripteurs.h sds.h constantes.h
	@gcc -c sauvegarde_descripteurs.c
	
config_reader.o: config_reader.c config_reader.h sds.h sauvegarde_descripteurs.h constantes.h
	@gcc -c config_reader.c
	
.PHONY: testSaveDesc.out
testSaveDesc.out: testSaveDesc.c sauvegarde_descripteurs.h sds.h sauvegarde_descripteurs.o sds.o
	@gcc -c testSaveDesc.c
	@gcc -o testSaveDesc.out testSaveDesc.o sauvegarde_descripteurs.o sds.o
	./testSaveDesc.out
	
.PHONY: testConfigFile.out
testConfigFile.out: testConfigFile.c sauvegarde_descripteurs.h sds.h config_reader.h config_reader.o sauvegarde_descripteurs.o sds.o
	@gcc -c testConfigFile.c
	@gcc -o testConfigFile.out testConfigFile.o sauvegarde_descripteurs.o sds.o config_reader.o
	./testConfigFile.out

test_indexation_audio.o: test_indexation_audio.c indexation_audio.h constantes.h sds.h sauvegarde_descripteurs.h
	@gcc -c test_indexation_audio.c

test_ia.out: test_indexation_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o
	@gcc -o test_ia.out test_indexation_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o

test_recherche_audio.o: test_recherche_audio.c recherche_audio.h indexation_audio.h constantes.h sds.h
	@gcc -c test_recherche_audio.c

test_ra.out: test_recherche_audio.o recherche_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o
	@gcc -o test_ra.out test_recherche_audio.o recherche_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o -lm

.PHONY: clean
clean:
	@rm -f *.o *.out
