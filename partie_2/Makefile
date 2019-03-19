libMoteurC.so: jni_MoteurC.o
	gcc -shared -o libMoteurC.so jni_MoteurC.o
	
jni_MoteurC.o: jni_MoteurC.c jni_MoteurC.h
	gcc -c -m64 -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -o jni_MoteruC.o c/jni_MoteurC.c
