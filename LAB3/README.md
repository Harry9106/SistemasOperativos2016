##### EXPLICACIÓN DE LO REALIZADO

En este laboratorio modificamos el planificador original que trae xv6 (Round Robin) por uno con colas de prioridades (Multi Level Feedback Queues). Modificamos los procesos para que tengan distintas prioridades y cantidades de timeslices según la cola a la que pertenezcan y sean premiados o castigados según lo que realizan. Mediante los programas de usuario frutaflops.c y verduiops.c realizamos pruebas para comparar los tipos de planificadores usados.

##### TRANSICIONES DE ESTADOS DE PROCESOS EN XV6 ORIGINAL (ROUND ROBIN)

SLEEPING -> RUNNABLE: esta transición sucede cuando un proceso esta bloqueado y tiene que ser reactivado para continuar su trabajo. Lo que hay que hacer es despertarlo con la función wakeup(void *chan), que recorre la tabla de procesos despertando a todos los procesos que estén durmiendo en ese canal y dejándolos listos para ejecución. 

RUNNABLE -> RUNNING: ya con el proceso despierto, se llama al scheduler() que recorre toda la tabla de procesos buscando algúno que este listo para ejecutar, cuando esto pasa se switchea a dicho proceso para que ejecute durante un timeslice y eventualmente devuelva el control al scheduler.

RUNNING -> RUNNABLE: en esta situación el proceso ha agotado su timeslice y tiene que detenerse. Esto se hace con yield(), que pone al proceso en listo para ejecutar y switchea al scheduler para elegir otro proceso.

RUNNING -> SLEEPING: en este punto el proceso se bloquea porque necesita alguna entrada desde teclado, disco, red, etc. antes de que termine su timeslice. Esto se hace mediante sleep() que lo pone a dormir y devuelve el control al scheduler.


##### TRANSICIONES DE ESTADOS DE PROCESOS EN XV6 MODIFICADO (MLFQ)

SLEEPING -> RUNNABLE: se recorre la tabla de procesos y con todos los que esten dormidos se hace lo siguiente: se los pone como listos para ejecutar, se les da más prioridad, se les da los tickets asociados a esa prioridad y por ultimo se los encola en la cola de prioridad correspondiente.

RUNNABLE -> RUNNING: se recorren las colas de prioridad de menor a mayor y si la cola no esta vacía se elige un proceso y se switchea para que ejecute durante los timeslices determinados por su prioridad.

RUNNING -> RUNNABLE: en esta situación el proceso ha agotado su timeslices por lo tanto aparte de dejarlo en listo para ejecutar, hay que darle menos prioridad, menos timeslices, colocarlo en la cola que ahora le corresponde y devolver el control al scheduler.

RUNNING -> SLEEPING: en este punto el proceso se bloquea porque necesita alguna entrada desde teclado, disco, red, etc. antes de que termine su timeslice. Esto se hace mediante sleep() que lo pone a dormir y devuelve el control al scheduler.