<h1 align="center">Proyecto Blockchain</h1>

**Proyecto 1 del curso de Estructura de Datos - 2023-I**

**Una aplicación de blockchain aplicado a transferencias bancarias**

**-----------------------------------------------------------------------------------**

Integrantes:
- Miguel Silva
- Juan Herencia
- Carlos Leonardo
- Judith Rojas



*1.	Descripción del caso de estudio planteado por el grupo*

1.1.	Problema
En las entidades bancarias y financieras, la seguridad y privacidad de los datos son aspectos críticos para las transacciones bancarias. Los sistemas tradicionales de almacenamiento y búsqueda de datos pueden presentar vulnerabilidades, y el acceso no autorizado a la información confidencial puede tener consecuencias graves, como el robo de identidad o el fraude financiero. Existe la necesidad de desarrollar una solución confiable y segura que garantice la protección de los datos transaccionales y, al mismo tiempo, permita búsquedas eficientes para su procesamiento. Debido a esa necesidad se propone la implementación de una solución basada en blockchain.

1.2.	Objetivos

1.2.1.	Objetivo General
Desarrollar una aplicación transaccional basada en blockchain y que sea segura y eficiente para el almacenamiento de datos de transferencias bancarias.

1.2.2.	Objetivos Específicos
	Desarrollar una aplicación transaccional de almacenamiento seguro de datos basada en la tecnología de cadenas de bloques (blockchain).
	Implementar un mecanismo de codificación para asegurar la integridad y confidencialidad de los datos almacenados en la cadena de bloques.
	Diseñar e implementar diferentes estructuras de datos para indexar los registros transaccionales, permitiendo búsquedas eficientes.
	Garantizar la escalabilidad de la solución, permitiendo el manejo de un gran volumen de transacciones bancarias de manera rápida y eficiente.

1.3.	Alcance
	Implementación de estructura de datos: Arreglo circular, lista circular doblemente enlazada, Hash, BST.
	Implementación del proof of work.
	Carga desde archivos csv.
	Ingreso de nuevas transacciones.
	Eliminación de transacciones y bloques.
	Modificación en los datos del bloque y recalculo en cascada.
	Búsquedas por índice, por un valor determinado, y un rango especificado.

2.	Importancia del Blockchain en el dominio de datos elegido
El blockchain ha demostrado ser una tecnología revolucionaria en el sector financiero y las transferencias bancarias por varias razones importantes:

	Seguridad: El blockchain ofrece una capa adicional de seguridad para las transacciones financieras. Al utilizar criptografía avanzada y técnicas de consenso distribuido, como la prueba de trabajo o la prueba de participación, el blockchain garantiza la integridad de los datos y evita la posibilidad de manipulación o alteración de la información financiera.
	Transparencia: La naturaleza transparente del blockchain permite a todas las partes involucradas en una transacción financiera ver y verificar la información. Esto ayuda a aumentar la confianza entre los participantes y a reducir la necesidad de intermediarios, ya que cada transacción queda registrada de forma inmutable y accesible para todos los participantes autorizados.
	Eficiencia y rapidez: Las transferencias bancarias a través del blockchain pueden agilizar significativamente el proceso, ya que eliminan la necesidad de verificaciones constantes. Al utilizar una red distribuida y descentralizada, las transacciones pueden realizarse en tiempo real y sin demoras significativas.
	Reducción de costos: El uso de blockchain en las transferencias bancarias puede reducir los costos asociados con los intermediarios y los procesos de liquidación. Al eliminar la necesidad de terceros de confianza y automatizar las transacciones, se pueden lograr ahorros significativos en comisiones y tarifas.
	Acceso global: El blockchain permite transferencias bancarias más accesibles a nivel global, especialmente en regiones donde el acceso a servicios financieros tradicionales es limitado. Las personas sin cuentas bancarias pueden participar en transacciones seguras y económicas utilizando billeteras digitales basadas en blockchain.
	Innovación y nuevos modelos de negocio: El blockchain ha estimulado la innovación en el sector financiero, permitiendo el desarrollo de nuevos modelos de negocio y servicios financieros. Las tecnologías basadas en blockchain, como los contratos inteligentes, han facilitado la creación de soluciones financieras descentralizadas y otras aplicaciones disruptivas.

En resumen, el blockchain ha transformado el sector financiero y las transferencias bancarias al proporcionar seguridad, transparencia, eficiencia y reducción de costos. Su capacidad para agilizar las transacciones, eliminar intermediarios y aumentar la confianza entre los participantes lo convierte en una herramienta poderosa para mejorar los servicios financieros a nivel global.

Así mismo su aplicación se ha visto expandida en otros sectores tales son los casos de:
	Cadena de suministro: El blockchain se utiliza para rastrear y auditar el movimiento de productos a lo largo de la cadena de suministro. Permite la verificación de la autenticidad, la trazabilidad de los productos y la reducción de fraudes en sectores como la alimentación, la moda y la industria farmacéutica [1].
	Salud: En el ámbito de la salud, el blockchain se utiliza para mantener registros médicos electrónicos seguros y compartidos, facilitando el intercambio de información entre proveedores de atención médica. También se emplea para la gestión de ensayos clínicos y el seguimiento de la cadena de frío en el transporte de medicamentos [2].
	Energía: El blockchain se utiliza para la gestión descentralizada de redes eléctricas, el seguimiento y certificación de energías renovables y la facilitación de transacciones peer-to-peer de energía. Ayuda a aumentar la eficiencia energética y a fomentar la adopción de energías limpias [3].
	Gobierno: El blockchain se ha explorado para mejorar la transparencia, la trazabilidad y la seguridad en los procesos gubernamentales, como la votación electrónica, la gestión de identidad y la administración de registros públicos. Ofrece la oportunidad de reducir la corrupción y aumentar la confianza ciudadana [4].
	Propiedad intelectual: El blockchain se utiliza para registrar y proteger la propiedad intelectual, como derechos de autor y patentes. Permite una prueba de existencia y autenticidad de los activos intangibles, agilizando los procesos de registro y protección [5].

3.	 Implementación
3.1.	Arquitectura
  











3.2.	Capa Vista
La vista se ha trabajo desde la misma consola, y lo hemos estructurado con un menú de opciones, para ello se ha generado la clase VistaBlockchain.h encargada de la gestión de las funcionalidades.
