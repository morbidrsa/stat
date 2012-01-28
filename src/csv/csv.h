/**
 * @brief Data structure to hold data
 *
 * This data structure holds all data on the events
 */
struct data {
	int when;		/** When did the event occure */
	int ammount;		/** How often did the event occure */
};

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
bool get_data_from_file(char *filename, struct data **ret, int *retcnt);
