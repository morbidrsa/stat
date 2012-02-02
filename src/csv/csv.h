/**
 * @brief Data structure to hold data
 *
 * This data structure holds all data on the events
 */
struct data {
	int when;		/** When did the event occure */
	int ammount;		/** How often did the event occure */
};

typedef bool (csv_callback) (int, int, void**, int*);

/**
 * @brief Initialize private csv parser context
 */
bool csv_init(void);

/**
 * @brief Free private csv parser context
 */
void csv_free(void);

/**
 * @brief Register fubction callback
 *
 * Register a callback function, which assigns the parsed fields into a
 * user defined data structure.
 *
 * @param cb	Parsing callback function
 */
void csv_register_callback(csv_callback *cb);

/**
 * @brief
 */
void csv_unregister_callback(void);

/**
 * @brief Get Data from File
 *
 * Read in CSV formated file and fill a data struct array
 *
 * @param filename 	the filename to read from
 * @param ret		pointer to data structure array the data is stored in
 * @param retcnt	Number of elements in ret data structure array
 *
 * @return true on success, false on failure
 */
bool csv_get_data_from_file(char *filename, struct data **ret, int *retcnt);
