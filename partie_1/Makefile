app.out: main.o indexation.o indexation_texte.o indexation_image.o indexation_audio.o recherche.o recherche_texte.o recherche_image.o recherche_audio.o
	@gcc -o app.out main.o indexation.o indexation_texte.o indexation_image.o indexation_audio.o recherche.o recherche_texte.o recherche_image.o recherche_audio.o

main.o: main.c indexation.h recherche.h
	@gcc -c main.c

indexation.o: indexation.c indexation.h indexation_texte.h indexation_image.h indexation_audio.h
	@gcc -c indexation.c

indexation_texte.o: indexation_texte.c indexation_texte.h
	@gcc -c indexation_texte.c

indexation_image.o: indexation_image.c indexation_image.h
	@gcc -c indexation_image.c

indexation_audio.o: indexation_audio.c indexation_audio.h
	@gcc -c indexation_audio.c

recherche.o: recherche.c recherche.h recherche_texte.h recherche_image.h recherche_audio.h
	@gcc -c recherche.c

recherche_texte.o: recherche_texte.c recherche_texte.h indexation_texte.h
	@gcc -c recherche_texte.c

recherche_image.o: recherche_image.c recherche_image.h indexation_image.h
	@gcc -c recherche_image.c

recherche_audio.o: recherche_audio.c recherche_audio.h indexation_audio.h
	@gcc -c recherche_audio.c
	
sds.o: sds.c sds.h sdsalloc.h
	@gcc -c sds.c
	
tstCreateDescripteurImage.out: tstCreateDescripteurImage.c indexation_image.h sds.h indexation_image.o sds.o
	@gcc -c tstCreateDescripteurImage.c
	@gcc -o tstCreateDescripteurImage.out tstCreateDescripteurImage.o sds.o indexation_image.o
	./tstCreateDescripteurImage.out

.PHONY: clean
clean:
	@rm -f *.o *.out
