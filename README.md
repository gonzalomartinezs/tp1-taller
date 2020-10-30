# Trabajo Práctico 1
### Taller de Programación I (75.42)

#### Martinez Sastre, Gonzalo Gabriel - 102321

Link al repositorio de Github: https://github.com/gonzalomartinezs/tp1-taller

## Introducción
El objetivo del presente trabajo consiste en realizar un cliente y un servidor capaces de enviar y recibir mensajes encriptados mediante algoritmos de cifrado de clave simétrica, respectivamente. El fin principal de esto reside en poner en práctica los conceptos vistos en clase sobre sockets, clientes y servidores.  

De esta manera, el emisor recibe la información por entrada estándar (`stdin`) y el receptor muestra la información descifrada por salida estándar (`stdout`).

## Desarrollo del programa
Para la realización de esta actividad se decidió dividir el desarrollo de la misma en bloques. Por este motivo, en un principio se procedió a codificar las bibliotecas de cifrado y, una vez finalizado esto, se procedió a probar el correcto funcionamiento de estas.

Una vez finalizado esto, se continuó con la implementación de los sockets. Al finalizar dicho proceso, se confeccionaron dos ejecutables que sólo utilizaban las primitivas de socket a modo de simular la funcionalidad de un cliente y un servidor. Al corroborar que era posible enviar y recibir mensajes sin cifrar exitosamente entre ambos, se siguió con el próximo paso.

A continuación, utilizando la biblioteca de sockets se procedió a realizar los TDAs Cliente y Servidor, y al igual que en la etapa anterior, se corroboró que se pudiera intercambiar mensajes exitosamente.

Tras esto, se procedió a juntar todo lo implementado hasta el momento de manera que se cumpliera la consigna. En este proceso, a fines de aumentar la cohesión y reducir el acomplamiento entre los TDAs implementados, se fueron creando bibliotecas tales como `Cipher` o `CommandParser`.

Finalmente,  una vez terminado todo lo anterior, se inició el proceso de debugging y refactorización, el cual se vió intercalado con entregas en el SERCOM. 

## Compilación y ejecución
Para compilar el programa simplemente se debe correr el comando:

```
make
```
Luego, se ejecutará el servidor con el siguiente comando:
```
./server <server-port> --method=<method> --key=<key>
```
Tras esto, el cliente se ejecuta como se muestra a continuación:
```
./client <server-host> <server-port> --method=<method> --key=<key>
```
De esta manera, quedará en espera a que se ingrese un mensaje por `stdin` y, al presionar `Ctrl+D`, se enviará la información cifrada al servidor, el cual mostrará el mensaje original.
Además, también se puede correr este programa utilizando el comando de redirección `< <filepath>` en el comando principal para enviar el contenido de un determinado archivo al servidor, como se indica debajo:

```
./client <server-host> <server-port> --method=<method> --key=<key> < <filepath>
```
Cabe destacar que el orden de los comandos debe ser igual al mostrado, de lo contrario el programa no funcionará.

Los opciones posibles para `method` son:
- `rc4` : Utilizará el algoritmo RC4 como método de encriptación.
- `cesar` : Utilizará el algoritmo de cifrado Cesar como método de encriptación.
- `vigenere` : Utilizará el algoritmo de cifrado Vigenère como método de encriptación.

Por otro lado, las opciones posibles para 'key' son:
- <ins>Valores numéricos</ins> : Para los tres métodos.
- <ins>Valores alfanuméricos</ins> : Para los métodos RC4 y Vigenère.


## Sobre el programa

### Estructura

Se puede decir que este programa se divide en dos bloques que resultan interesantes de analizar. Por un lado, se encuentra la interacción cliente-servidor por medio de mensajes cifrados y, por el otro, la relación entre el TDA Cipher y cada uno de los posibles algoritmos de encriptación.

A continuación se muestra un diagrama que resume este primer bloque.

![alt text][cliente-servidor]

Como se puede observar tanto el cliente como el servidor cuentan con un socket propio utilizado para establecer la conexión. Además, por su parte, el servidr cuenta con un socket peer el cual utilizará para recibir la información enviada por el cliente. Cabe destacar, que ambos TDAs crean una instancia del Cipher dentro de sus respectivas funciones de envió o recepción de información.

Por su parte, la relación del Cipher con los distintos algoritmos se logra mediante el siguiente esquema.

![alt text][cifradores]

Resulta interesante nombrar la inclusión de los punteros a función `EncryptFunc` dentro del TDA Cipher. De esta manera cada algoritmo, le envía al cifrador un puntero a sus funciones de encriptación/decriptación. Por último, esta estructura también cuenta con un `CipherInfo` el cual contiene la información necesaria para que los distintos algoritmos se puedan ejecutar correctamente.


### Flujo de ejecución

El aspecto principal de este programa reside en el envío y la recepción de mensajes cifrados. Es por ellos que los diagramas de esta sección esquematizan el flujo del programa en dichas acciones.

![alt text][send]

Por un lado, este diagrama resume a grandes rasgos lo que ocurre dentro de la función `clientEncryptAndSend()` del cliente. En primer lugar se crea una instancia del TDA Cipher (el cual toma las funciones de encriptación de acuerdo al método escogido por el usuario), luego se comienza a leer el archivo (en este caso, `stdin`) de a chunks de 64 bytes. Tras leer un chunk, este es enviado al cifrador el cual devuelve un bloque de igual tamaño con el mensaje encriptado. Luego, este bloque es enviado byte a byte al servidor mediante `socketSend()`. Posteriormente, se lee otro chunk y el proceso se repite hasta el final del archivo o el surgimiento de un error.
  
![alt text][recv]

Por otra parte, el proceso que ejecuta el servidor es el inverso al anterior. En primer lugar se recibe un chunk de 64 bytes, se lo desencripta y se lo escribe en el archivo de salida (aquí `stdout`). Luego, se lee otro chunk y se repite sucesivamente este proceso hasta que se dejen de recibir bytes de información.

### Detalles de implementación
En esta sección se indican algunas suposiciones realizadas y decisiones tomadas a la hora de desarrollar el programa.

- En todo momento se trata a los atributos de todos los TDAs como privados.

- La mayoría de las funciones son de tipo de retorno entero. Esto se realizó así con el fin de poder informar y validar los errores en tiempo de ejecución.

- Si surge un error durante la ejecución de cierta tarea la encargada de informárselo al usuario es la función en curso.

- En caso de error, las funciones `socketSend()` y `socketReceive()` retornan `ERROR` y dejan en manos del usuario la acción de cerrar o no dicho socket.

- Si surge un error mientras se envía información, se procede a cerrar el cliente. Por otro lado, si ocurre algún imprevisto mientras se reciben bytes se cierra el socket peer del servidor, pero no el servidor en sí.

- Si bien la implementación del server se encuentra diseñada para aceptar un único cliente en simultáneo, algunas funciones apuntan al hecho de que se puedan aceptar varios clientes (como serverAccept). Esto se debe a que si en un futuro se desea realizar dicha modificación, no sea necesario realizar cambios en toda la biblioteca.

### Fixes
Para la reentrega del presente trabajo se realizó la siguiente modificación del modelo. Ahora el TDA Cipher contiene una instancia de cada TDA de cifrado (Caesar, RC4 y Vigenere) y el nombre del método a utilizar, en base al cual se elige a qué función de cifrado llamar. Además, dichos TDAs de cifrado ya no dependen de `CipherInfo`, sino que cada uno de ellos contiene toda la información necesaria para realizar las operaciones de codificación/decodificación.

De esta manera, el diagrama UML actualizado resulta como se muestra a continuación.

![alt text][cifradores_fixed]

Asimismo, al actualizar el esquema de la relación cliente-servidor se observa lo siguiente.

![alt text][cliente-servidor_fixed]

## Conclusión

Este trabajo resultó de gran ayuda para comprender el funcionamiento de un socket y de un esquema cliente servidor. Además, el hecho de haberlo realizado en el lenguaje de progrmación C permite comprender en buena medida cómo funciona este aspecto básico y fundamental para un ingeniero informático/licenciado y que, a día de hoy, forma parte de la vida cotidiana de todos.



[cliente-servidor]:https://github.com/gonzalomartinezs/tp1-taller/blob/master/img/cl-sv.png
[cliente-servidor_fixed]:https://github.com/gonzalomartinezs/tp1-taller/blob/master/img/cl-sv_fixed.png
[cifradores]:https://github.com/gonzalomartinezs/tp1-taller/blob/master/img/cifradores.png
[cifradores_fixed]:https://github.com/gonzalomartinezs/tp1-taller/blob/master/img/cifradores_fixed.png
[send]:https://github.com/gonzalomartinezs/tp1-taller/blob/master/img/send.png
[recv]:https://github.com/gonzalomartinezs/tp1-taller/blob/master/img/recv.png