app.out: main.o indexation.o indexation_texte.o indexation_image.o indexation_audio.o recherche.o recherche_image.o recherche_audio.o recherche_texte.o sds.o sauvegarde_descripteurs.o config_reader.o
	@gcc -o app.out $(DEBUG) main.o indexation.o indexation_texte.o indexation_image.o indexation_audio.o recherche.o recherche_image.o recherche_audio.o recherche_texte.o sds.o sauvegarde_descripteurs.o config_reader.o -lm
	
main.o: main.c indexation.h sds.h constantes.h config_reader.h sauvegarde_descripteurs.h recherche.h
	@gcc -c main.c

indexation.o: indexation.c indexation.h indexation_texte.h indexation_image.h indexation_audio.h sauvegarde_descripteurs.h config_reader.h constantes.h
	@gcc -c indexation.c
	
recherche.o: recherche.c recherche.h recherche_texte.h recherche_image.h recherche_audio.h sauvegarde_descripteurs.h config_reader.h constantes.h
	@gcc -c $(DEBUG) recherche.c

indexation_texte.o: indexation_texte.c indexation_texte.h sds.h constantes.h sauvegarde_descripteurs.h config_reader.h
	@gcc -c indexation_texte.c

indexation_image.o: indexation_image.c indexation_image.h sds.h
	@gcc -c indexation_image.c  -lm

indexation_audio.o: indexation_audio.c indexation_audio.h
	@gcc -c indexation_audio.c

recherche_texte.o: recherche_texte.c recherche_texte.h indexation_texte.h
	@gcc -c $(DEBUG) recherche_texte.c

recherche_image.o: recherche_image.c recherche_image.h indexation_image.h sds.h sauvegarde_descripteurs.h
	@gcc -c recherche_image.c -lm

recherche_audio.o: recherche_audio.c recherche_audio.h indexation_audio.h constantes.h
	@gcc -c recherche_audio.c
	
sds.o: sds.c sds.h sdsalloc.h
	@gcc -c sds.c

sauvegarde_descripteurs.o: sauvegarde_descripteurs.c sauvegarde_descripteurs.h sds.h constantes.h
	@gcc -c sauvegarde_descripteurs.c
	
config_reader.o: config_reader.c config_reader.h sds.h sauvegarde_descripteurs.h constantes.h
	@gcc -c config_reader.c

tst_recherche_texte.o: tst_recherche_texte.c sds.h indexation_texte.h recherche_texte.h sauvegarde_descripteurs.h
	@gcc -c tst_recherche_texte.c

tst_recherche_texte.out : tst_recherche_texte.o sds.o indexation_texte.o recherche_texte.o sauvegarde_descripteurs.o config_reader.o
	@gcc -o tst_recherche_texte.out tst_recherche_texte.o sds.o indexation_texte.o recherche_texte.o sauvegarde_descripteurs.o config_reader.o
	
.PHONY: testSaveDesc.out
testSaveDesc.out: testSaveDesc.c sauvegarde_descripteurs.h sds.h sauvegarde_descripteurs.o sds.o
	@gcc -c testSaveDesc.c
	@gcc -o testSaveDesc.out testSaveDesc.o sauvegarde_descripteurs.o sds.o
	./testSaveDesc.out
	
.PHONY: testSaveDescStupideFaconLoic.out
testSaveDescFaconLoic.out: testSaveDescStupideFaconLoic.c sauvegarde_descripteurs.h sds.h sauvegarde_descripteurs.o sds.o
	@gcc -c testSaveDescStupideFaconLoic.c
	@gcc -o testSaveDescStupideFaconLoic.out testSaveDescStupideFaconLoic.o sauvegarde_descripteurs.o sds.o
	./testSaveDescStupideFaconLoic.out
	
.PHONY: testConfigFile.out
testConfigFile.out: testConfigFile.c sauvegarde_descripteurs.h sds.h config_reader.h config_reader.o sauvegarde_descripteurs.o sds.o
	@gcc -c testConfigFile.c
	@gcc -o testConfigFile.out testConfigFile.o sauvegarde_descripteurs.o sds.o config_reader.o
	./testConfigFile.out

.PHONY: test_indexation_texte.out
test_indexation_texte.out : test_indexation_texte.c sds.h sds.o indexation_texte.h indexation_texte.o sauvegarde_descripteurs.h sauvegarde_descripteurs.o config_reader.h config_reader.o
	@gcc -c test_indexation_texte.c
	@gcc -o test_indexation_texte.out test_indexation_texte.o sds.o indexation_texte.o config_reader.o sauvegarde_descripteurs.o -lm
	./test_indexation_texte.out
	
.PHONY: test_genere_table.out
test_genere_table.out : test_genere_table.c sds.h sds.o indexation_texte.h indexation_texte.o sauvegarde_descripteurs.h sauvegarde_descripteurs.o config_reader.h config_reader.o
	@gcc -c test_genere_table.c
	@gcc -o test_genere_table.out test_genere_table.o sds.o indexation_texte.o config_reader.o sauvegarde_descripteurs.o -lm
	./test_genere_table.out
	
.PHONY: test_indexation_texte_lecture_fichier.out
test_indexation_texte_lecture_fichier.out : test_indexation_texte_lecture_fichier.c sds.h sds.o indexation_texte.h indexation_texte.o
	@gcc -c test_indexation_texte_lecture_fichier.c
	@gcc -o test_indexation_texte_lecture_fichier.out test_indexation_texte_lecture_fichier.o sds.o indexation_texte.o -lm
	./test_indexation_texte_lecture_fichier.out
	
.PHONY: tst_tabocc.out
tst_tabocc.out:indexation_texte.h indexation_texte.o sds.h sds.o
	@gcc -c tst_tabocc.c
	@gcc -o tst_tabocc.out tst_tabocc.o sds.o indexation_texte.o
	./tst_tabocc.out
	
test_indexation_audio.o: test_indexation_audio.c indexation_audio.h constantes.h sds.h sauvegarde_descripteurs.h
	@gcc -c test_indexation_audio.c

test_ia.out: test_indexation_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o
	@gcc -o test_ia.out test_indexation_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o

test_recherche_audio.o: test_recherche_audio.c recherche_audio.h indexation_audio.h constantes.h sds.h
	@gcc -c test_recherche_audio.c

test_ra.out: test_recherche_audio.o recherche_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o
	@gcc -o test_ra.out test_recherche_audio.o recherche_audio.o indexation_audio.o sds.o sauvegarde_descripteurs.o -lm

.PHONY: tstCreateDescripteurImage.out
tstCreateDescripteurImage.out: tstCreateDescripteurImage.c indexation_image.h sds.h indexation_image.o sds.o
	@gcc -c tstCreateDescripteurImage.c
	@gcc -o tstCreateDescripteurImage.out tstCreateDescripteurImage.o sds.o indexation_image.o -lm
	./tstCreateDescripteurImage.out
	
.PHONY: tstDecodeDescImage.out
tstDecodeDescImage.out: tstDecodeDescImage.c recherche_image.h recherche_image.o sds.h sds.o indexation_image.o indexation_image.h
	@gcc -c tstDecodeDescImage.c
	@gcc -o tstDecodeDescImage.out tstDecodeDescImage.o sds.o recherche_image.o indexation_image.o -lm
	./tstDecodeDescImage.out

.PHONY: TestIndexationImage.out
TestIndexationImage.out: indexation_image.o sds.o TestIndexationImage.c indexation_image.h sds.h
	@gcc -c TestIndexationImage.c
	@gcc -o TestIndexationImage.out TestIndexationImage.o indexation_image.o sds.o -lm
	./TestIndexationImage.out

.PHONY:test_recherche_image1.out
test_recherche_image1.out: test_recherche_image1.c recherche_image.h recherche_image.o indexation_image.o sds.h sds.o sauvegarde_descripteurs.h sauvegarde_descripteurs.o
	@gcc -c test_recherche_image1.c
	@gcc -o test_recherche_image1.out test_recherche_image1.o recherche_image.o indexation_image.o sds.o sauvegarde_descripteurs.o -lm
	./test_recherche_image1.out
	
.PHONY:test_recherche_image2.out
test_recherche_image2.out: test_recherche_image2.c recherche_image.h recherche_image.o indexation_image.o sds.h sds.o sauvegarde_descripteurs.h sauvegarde_descripteurs.o
	@gcc -c test_recherche_image2.c
	@gcc -o test_recherche_image2.out test_recherche_image2.o recherche_image.o indexation_image.o sds.o sauvegarde_descripteurs.o -lm
	./test_recherche_image2.out

.PHONY:test_desc_gris.out
test_desc_gris.out: test_desc_gris.c recherche_image.h recherche_image.o indexation_image.o sds.h sds.o sauvegarde_descripteurs.h sauvegarde_descripteurs.o
	@gcc -c test_desc_gris.c
	@gcc -o test_desc_gris.out test_desc_gris.o recherche_image.o indexation_image.o sds.o sauvegarde_descripteurs.o -lm
	./test_desc_gris.out
	
.PHONY:test_indexation.out
test_indexation.out: test_indexation.c indexation.o indexation.h sauvegarde_descripteurs.h sauvegarde_descripteurs.o sds.o
	@gcc -c test_indexation.c
	@gcc -o test_indexation.out test_indexation.o sauvegarde_descripteurs.o indexation.o sds.o -lm
	./test_indexation.out

	
.PHONY: clean
clean:
	@rm -f *.o *.out
