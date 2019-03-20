libMoteurC.so: jni_MoteurC.o
	gcc -shared -o libMoteurC.so jni_MoteurC.o
	
jni_MoteurC.o: c/jni_MoteurC.c c/jni_MoteurC.h
	gcc -c -m64 -I"$$JAVA_HOME/include" -I"$$JAVA_HOME/include/linux" -o jni_MoteurC.o c/jni_MoteurC.c

.PHONY: clean
clean:
	@rm -f *.o *.so *.dll