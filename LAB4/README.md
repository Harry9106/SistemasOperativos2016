##### EXPLICACIÓN DE LO REALIZADO

En este laboratorio implementamos permisos para el sistema de archivos de xv6. Nos basamos en el esquema de permisos de UNIX el cual tiene tres tipos de permisos: lectura (R), escritura (W) y ejecución (X). La única diferencia es que en vez de tener las tres clases de usuarios originales, en nuestro caso, solo implementamos los permisos para el dueño de los archivos ya que xv6 es mono-usuario.

##### PERMISOS A INODOS

Primero tuvimos que modificar las estructuras originales de xv6 para agregar un campo que guardara los permisos. Para esto le sacamos 3 bits al campo minor que quedo con 13. Esto se hizo así ya que el tamaño de las estructuras tiene que permanecer igual para que no haya conflictos. Los archivos donde hicimos esto fueron fs.h, file.h y stat.h.

##### IMPLEMENTACION CHMOD

Para la implementación de chmod tuvimos que crear una nueva syscall llamada sys_chmod y un programa de usuario. Sus parámetros son el nombre del archivo y un numero entero entre 0 y 7 que se corresponde con los bits de permisos que se desean activar/desactivar. La decisión de diseño fue reescribir todos los bits de permisos según el parámetro recibido, en vez de activar/desactivar bit a bit. El argumento perm queda determinado por la siguiente tabla:

| PERM 	| READ 	| WRITE 	| EXECUTE 	|
|------	|------	|-------	|---------	|
| 0    	| 0    	| 0     	| 0       	|
| 1    	| 0    	| 0     	| 1       	|
| 2    	| 0    	| 1     	| 0       	|
| 3    	| 0    	| 1     	| 1       	|
| 4    	| 1    	| 0     	| 0       	|
| 5    	| 1    	| 0     	| 1       	|
| 6    	| 1    	| 1     	| 0       	|
| 7    	| 1    	| 1     	| 1       	|

Usamos las constantes S_IREAD, S_IWRITE, S_IEXEC, definidas en fcntl.h, como flags para realizar las operaciones con los bits de permisos.

##### CUMPLIMIENTO DE PERMISOS

Ya teniendo todo implementado, hicimos cumplir los permisos.
Empezamos por el de ejecución (X) modificando en exec.c y luego de varios intentos fallidos decidimos crear una función en fs.c que nos devolviera los permisos de un inodo ya que necesitábamos esa información y haciendo include traía mas problemas que soluciones.
Para el cumplimiento de la lectura y escritura modificamos en file.c las funciones fileread y filewrite para que realicen el chequeo pertinente antes de hacer cualquier cosa. Cambien modificamos la syscall sys_open seteando las variables de archivo readable y writable según los permisos del inodo al que hacen referencia.
La decisión de diseño aquí fue decidir si se debía abrir el archivo solo si el modo de apertura coincidía con los permisos del inodo de ese archivo, o abrir siempre el archivo y luego permitir la lectura o escritura según los permisos. Optamos por lo segundo ya que encontramos algunos problemas con la primera idea.


##### IMPRESIÓN EN PANTALLA DE PERMISOS

Para finalizar modificamos el programa de usuario ls.c agregándole un flag (-l) para que muestre los permisos que tienen los archivos. Los permisos aparecen en la ultima columna y se corresponden directamente con la tabla mencionada previamente.