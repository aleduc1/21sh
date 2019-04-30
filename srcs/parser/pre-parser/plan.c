/* Goal :
 * Need a token containing whats needed for redirect in a struct for all redirect token
 * 
 * Step :
 * 1st step -> Link everything related to the redirection into a single token
 * 2nd step -> Malloc and fill the struct inside the token
 *
 * Do this after having the simple command refactor
 * Refactor whats inside the simple command now
 * A redirect token can contain : 
 * - Source fd
 * - Dest fd
 * - File
 * - Redirect token
 */
