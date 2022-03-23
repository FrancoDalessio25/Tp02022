#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log "
    log_info(logger,"Hola! Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	valor = config_get_string_value(config,"CLAVE");
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor '

	// Loggeamos el valor de config
	log_info(logger,valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	if((nuevo_logger = log_create("/home/utnso/tp0/tp0.log","tp0",true,LOG_LEVEL_INFO)) == NULL){
		printf("No se puede loggear");
		abort();
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	

	if((nuevo_config = config_create("/home/utnso/tp0/tp0.config")) == NULL){

		perror("No se pudo crear la config!\n");
		abort();
	}


	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	while (!string_is_empty(leido = readline(">"))) {

		if (leido == NULL) {

			perror("No se puede leer esa linea");
			abort();
		}

		log_info(logger, leido);
		free(leido);
	}

	free(leido);

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío


	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	t_log* logger;
	int tamanio;

	paquete = crear_super_paquete();

	while (!string_is_empty(leido = readline(">"))) {

			if (leido == NULL) {

				perror("No se puede leer esa linea");
				abort();
			}

			tamanio = strlen(leido) + 1;
			agregar_a_paquete(paquete, (void*) leido, tamanio);
			free(leido);
		}

		free(leido);

		enviar_paquete(paquete, conexion);

		eliminar_paquete(paquete);
	free(leido);
	// Leemos y esta vez agregamos las lineas al paquete


	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	close(conexion);
	log_destroy(logger);
	config_destroy(config);

}

