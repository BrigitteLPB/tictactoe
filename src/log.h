#ifndef LOG_H_
	#define LOG_H_

	/*--- INLCUDE ---*/
	#include <stdio.h>

	/*--- VARS and CONSTS ---*/

	/**
	 * @brief les types de logs a effectuer
	 * 
	 */
	typedef enum
	{
		INFO,
		WARN,
		ERROR,
		DEBUG
	} log_state_e;

	/*--- FUNCTION ---*/

	/**
	 * @brief initialise le module de log
	 * 
	 * @param [in] console le pointeur sur le flux de sortie en console
	 * @param fichier le pointeur sur le flux de sortie en fichier
	 */
	void log_init(FILE* console, FILE* fichier);

	/**
	 * @brief desctructeur de log. N'effectue pas un fclose sur les fichiers
	 * 
	 */
	void log_free();

	/**
	 * @brief log a message
	 * 
	 * @param [in] type	le type de message a afficher
	 * @param [in] message le message a afficher 
	 */
	void log_m(log_state_e type, char message[]);


#endif