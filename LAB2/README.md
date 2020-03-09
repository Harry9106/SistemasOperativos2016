##### EXPLICACIÓN DE LO REALIZADO

En este laboratorio lo que hicimos fue implementar semáforos nombrados para la sincronización entre procesos en xv6.
Para ello primero implementamos las syscalls sem_init, sem_release, sem_down y sem_up las cuales sirven para usar los semáforos en espacio de usuario.
Mediante los programas de usuario barrier_init, barrier_echo y barrier_rise testeamos el funcionamiento de los semáforos.
Al corroborar el correcto funcionamiento de la implementación procedimos a crear un programa de usuario llamado pingpong, que imprime las palabras ping y pong intercaladamente usando dos procesos que están sincronizados gracias a los semáforos.

##### EXPLICACIÓN DE "$" y "zombie!" EN BARRIERS

Básicamente un proceso zombie es un proceso que ha acabado su ejecución, desreferenciado toda su memoria y recursos asociados a él pero cuya entrada de proceso todavía se encuentra en la tabla de procesos.
Para solucionar esto es necesario que el proceso padre del proceso zombie haga una llamada a la función wait() que se encarga de liberar esa entrada en la tabla mencionada.
Lo que sucede con los procesos barriers es que al finalizar su ejecución con la función exit(), estos quedan en estado zombie esperando a que su padre haga wait() para darse cuenta que finalizaron. Pero esto no sucede y por eso aparece el mensaje zombie!

##### EXPLICACIÓN DE acquire, release, sleep, wakeup y argint

Acquire: deshabilita las interrupciones, chequea si el lock ya esta agarrado, si es así entra en pánico, sino spinea hasta agarrar el lock, sincroniza compilador y cpu para no hacer nada durante la sección critica, recolecta información del lock para debugging.

Release: chequea si el lock no esta agarrado, si es asi entra en panico, sino resetea la información del debugging, sincroniza compilador y cpu para hacer visible lo hecho en la sección critica a los otros cores, suelta el lock atomicamente, habilita las interrupciones.

Sleep: agarra el lock de la tabla de procesos para liberar el lock que tenia el proceso, lo hace dormir, llama al planificador, cuando se despierta devuelve el lock de la tabla de procesos y agarra el lock original que tenia.

Wakeup: agarra el lock de la tabla de procesos, despierta todos los procesos, libera el lock de la tabla de procesos.

Argint: recupera el n-esimo argumento entero de la syscall.