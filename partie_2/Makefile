libMoteurC.so: jni_MoteurC.o utility.o
	gcc -shared -o libMoteurC.so jni_MoteurC.o utility.o ../partie_1/indexation_audio.o ../partie_1/indexation_image.o ../partie_1/indexation_texte.o ../partie_1/recherche_audio.o ../partie_1/recherche_image.o ../partie_1/recherche_texte.o ../partie_1/sauvegarde_descripteurs.o ../partie_1/sds.o
	
jni_MoteurC.o: c/jni_MoteurC.c c/jni_MoteurC.h c/utility.h
	gcc -c -m64 -I"$$JAVA_HOME/include" -I"$$JAVA_HOME/include/linux" -I"../" -o jni_MoteurC.o c/jni_MoteurC.c

utility.o: c/utility.c c/utility.h
	gcc -c -I"../" c/utility.c -o utility.o

.PHONY: clean
clean:
	@rm -f *.o *.so *.dll