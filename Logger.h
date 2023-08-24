#ifndef SOLVER_LOGGER
#define SOLVER_LOGGER

/// @brief Size of a buffer which contains logged functions
const int TRACE_BUFFER_SIZE = 20;

/// @brief Struct for storing data about logged function
struct LOGGED_FUNCTION{
    char file[FILENAME_MAX];
    char function[FILENAME_MAX];
    int line;
};

/*!
    @brief Stores data about logged function in buffer
    @param[in] file Name of file where logged function is contained
    @param[in] function Logged function name
    @param[in] line Number of line where function was logged
    @return Nothing
    Stores file, function and line data in the next available buffer cell
*/
void add_func_to_log (const char *file, const char *function, int line);

/*!
    @brief Prints stack trace
    @return Nothing
    Prints stack trace if SHOW_STACK_TRACE option is enabled
*/
void Show_stack_trace ();

/*!
    @brief Logs exit from a function
    @return Nothing
*/
void pop_func_from_log ();

/*!
    @brief Allocates memory for log buffer
    @return Nothing
    @note Must be called before logging starts
*/
void open_log();

/*!
    @brief Deallocates log buffer memory
    @return Nothing
    @note Must be called in atexit function
*/
void close_log();

/// @brief Buffer for information about traced functions
extern struct LOGGED_FUNCTION *Stack_trace_buffer;

#ifdef _SHOW_STACK_TRACE

/*! @brief Adds function to log */
#define AddLog                                                              \
            do{                                                             \
                add_func_to_log (__FILE__, __PRETTY_FUNCTION__, __LINE__);  \
            }while (0)

/*! @brief Pops function from log */
#define PopLog                          \
            do{                         \
                pop_func_from_log ();   \
            }while (0)

#else

#define Log ;
#define PopLog ;

#endif



#endif