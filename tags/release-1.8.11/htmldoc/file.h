/*
 * "$Id: file.h,v 1.6.2.1 2001/02/02 15:10:57 mike Exp $"
 *
 *   Filename definitions for HTMLDOC, a HTML document processing program.
 *
 *   Copyright 1997-2001 by Easy Software Products.
 *
 *   These coded instructions, statements, and computer programs are the
 *   property of Easy Software Products and are protected by Federal
 *   copyright law.  Distribution and use rights are outlined in the file
 *   "COPYING.txt" which should have been included with this file.  If this
 *   file is missing or damaged please contact Easy Software Products
 *   at:
 *
 *       Attn: ESP Licensing Information
 *       Easy Software Products
 *       44141 Airport View Drive, Suite 204
 *       Hollywood, Maryland 20636-3111 USA
 *
 *       Voice: (301) 373-9600
 *       EMail: info@easysw.com
 *         WWW: http://www.easysw.com
 */

#ifndef _FILE_H_
#  define _FILE_H_

/*
 * Include necessary headers...
 */

#  include "string.h"

#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */


/*
 * Prototypes...
 */

extern char	*file_basename(const char *s);
extern char	*file_directory(const char *s);
extern char	*file_extension(const char *s);
extern char	*file_find(const char *path, const char *s);
extern char	*file_localize(const char *filename, const char *newcwd);
extern char	*file_method(const char *s);
extern void	file_proxy(const char *url);
extern char	*file_target(const char *s);

#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /* !_FILE_H_ */

/*
 * End of "$Id: file.h,v 1.6.2.1 2001/02/02 15:10:57 mike Exp $".
 */