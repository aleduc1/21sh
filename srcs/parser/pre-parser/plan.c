/* Goal :
 * Need a token containing whats needed for redirect in a struct for all redirect token
 * 
 * Step :
 * 1st step -> Link everything related to the redirection into a single token
 * 2nd step -> Malloc and fill the struct inside the token
 *
 * Need to implement whitespace token before this to determine fd or filename in some cases
 * Do this after before the simple command refactor
 *
 * A redirect token can contain : 
 * - Source fd
 * - Dest fd
 * - File
 * - Redirect token
 *
 * Rules :
 * 
 * For > token :
 *
 * Everything right : filename
 * Numbers left whitout space : src_fd
 * 
 *
 * For >& token :
 *
 * Numbers left without space : src_fd
 * Every numbers right : dest_fd
 * Everything else right : filename
 *
 * 
 * For &> token :
 * 
 * Everything left : nothing
 * Everything right : filename
 *
 * 
 * For < token :
 *
 * Everything left : nothing
 * Everything right : filename (stdin)
 *
 *
 * For <& token :
 *
 * Everything left : nothing
 * Everything right : 
 *
 *
 * For &< token :
 *
 * Everything left :
 * Everything right :
 *
 *
 * For >> token :
 * 
 * Handle same way as >
 * 
 *
 *
 * Default fd value :
 *
 * >  = 1
 * >& = 1 2
 * &> = 1 2
 * <  = 0
 * <& = 1
 * &< = 1
 * >> = 1
 * << = 0
 */
