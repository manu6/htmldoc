//
// "$Id: teststyle.cxx,v 1.1.2.5 2005/05/07 03:02:38 mike Exp $"
//
//   Stylesheet test program for HTMLDOC, a HTML document processing program.
//
//   Copyright 1997-2005 by Easy Software Products.
//
//   These coded instructions, statements, and computer programs are the
//   property of Easy Software Products and are protected by Federal
//   copyright law.  Distribution and use rights are outlined in the file
//   "COPYING.txt" which should have been included with this file.  If this
//   file is missing or damaged please contact Easy Software Products
//   at:
//
//       Attn: ESP Licensing Information
//       Easy Software Products
//       44141 Airport View Drive, Suite 204
//       Hollywood, Maryland 20636 USA
//
//       Voice: (301) 373-9600
//       EMail: info@easysw.com
//         WWW: http://www.easysw.com
//
// Contents:
//
//

//
// Include necessary headers.
//

#include "hdstring.h"
#include "style.h"
#include "progress.h"


//
// Global stuff for testing...
//

const char	*_htmlData = "..";


//
// 'progress_error()' - Display an error message.
//

void
progress_error(hdError    error,	// I - Error number
               const char *format,	// I - Printf-style format string
               ...)			// I - Additional args as needed
{
  va_list	ap;			// Argument pointer


  va_start(ap, format);
  vfprintf(stderr, format, ap);
  putc('\n', stderr);
  va_end(ap);
}


void
progress_hide(void)
{
}


void
progress_show(const char *format, ...)
{
}


void
progress_update(int percent)
{
}


//
// 'main()' - Test the stylesheet loading code.
//

int					// O - Exit status
main(int  argc,				// I - Number of command-line args
     char *argv[])			// I - Command-line arguments
{
  FILE		*fp;			// Stylesheet file
  hdStyleSheet	*css;			// Stylesheet data
  hdStyle	*style;			// Style data
  int		i, j;			// Looping vars
  static const char * const		// Enumeration strings...
		pos[4] = { "bottom", "left", "right", "top" };
  static const char * const
		background_repeat[] = { "inherit", "repeat", "repeat-x",
		                        "repeat-y", "no-repeat" };
  static const char * const
		border_style[] = { "inherit", "none", "dotted", "dashed",
		                   "solid", "double", "groove", "ridge",
				   "inset", "outset" };
  static const char * const
		caption_side[] = { "top", "bottom" };
  static const char * const
		clear[] = { "inherit", "none", "left", "right", "both" };
  static const char * const
		display[] = { "inherit", "none", "block", "compact", "inline",
		              "inline-table", "list-item", "marker",
			      "run-in", "table", "table-caption", "table-cell",
			      "table-column", "table-column-group",
			      "table-footer-group", "table-header-group",
			      "table-row", "table-row-group" };
  static const char * const
		float_[] = { "inherit", "none", "left", "right" };
  static const char * const
		font_style[] = { "inherit", "normal", "italic", "oblique" };
  static const char * const
		font_variant[] = { "inherit", "normal", "small-caps" };
  static const char * const
		font_weight[] = { "inherit", "normal", "bold" };
  static const char * const
		list_style_position[] = { "inherit", "inside", "outside" };
  static const char * const
		list_style_type[] = { "inherit", "none", "disc",
				      "circle", "square",
				      "decimal", "lower-roman",
				      "upper-roman",
				      "lower-alpha",
				      "upper-alpha" };
  static const char * const
		page_break[] = { "inherit", "auto", "always", "avoid", "left", "right" };
  static const char * const
		text_align[] = { "inherit", "left", "center", "right", "justify" };
  static const char * const
		text_decoration[] = { "inherit", "none", "underline", "overline",
		                      "line-through" };
  static const char * const
		text_transform[] = { "inherit", "none", "capitalize", "uppercase",
		                     "lowercase"};
  static const char * const
		vertical_align[] = { "inherit", "baseline", "sub", "super", "top",
		                     "text-top", "middle", "bottom",
				     "text-bottom" };
  static const char * const
		white_space[] = { "inherit", "normal", "nowrap", "pre",
		                  "pre-wrap", "pre-line" };


  // Check command-line...
  if (argc < 2)
  {
    puts("Usage: teststyle filename.css");
    return (1);
  }

  // Load the stylesheet...
  if ((fp = fopen(argv[1], "r")) == NULL)
  {
    perror(argv[1]);
    return (1);
  }

  css = new hdStyleSheet();

  css->load(fp, ".");
  css->set_line_height("1.1");
  css->update_styles();

  fclose(fp);

  // Show all of the styles...
  printf("\"%s\": %d styles...\n\n", argv[1], css->num_styles);

  for (i = 0; i < css->num_styles; i ++)
  {
    style = css->styles[i];

    if (style->selectors[0].id && !strncmp(style->selectors[0].id, "_HD", 3))
      continue;

    for (j = style->num_selectors - 1; j >= 0; j --)
    {
      fputs(css->get_element(style->selectors[j].element), stdout);

      if (style->selectors[j].class_)
        printf(".%s", style->selectors[j].class_);

      if (style->selectors[j].pseudo)
        printf(":%s", style->selectors[j].pseudo);

      if (style->selectors[j].id)
        printf("#%s", style->selectors[j].id);

      putchar(' ');
    }

    puts("{");

    if (style->background_color_set != HD_COLOR_INHERIT ||
        style->background_image ||
	style->background_repeat != HD_BACKGROUND_REPEAT_INHERIT ||
        style->background_position[0] != HD_WIDTH_AUTO ||
        style->background_position[1] != HD_WIDTH_AUTO)
    {
      printf("  background:");

      if (style->background_color_set == HD_COLOR_TRANSPARENT)
        fputs(" transparent", stdout);
      else if (style->background_color_set == HD_COLOR_SET)
	printf(" rgb(%d,%d,%d)", style->background_color[0],
               style->background_color[1], style->background_color[2]);

      if (style->background_image)
	printf("  url(%s)", style->background_image);

      if (style->background_repeat != HD_BACKGROUND_REPEAT_INHERIT)
        printf(" %s", background_repeat[style->background_repeat]);

      for (j = 0; j < 2; j ++)
	if (style->background_position_rel[j])
          printf(" %s (%.1f)", style->background_position_rel[j],
	         style->background_position[j]);
	else if (style->background_position[j] == HD_WIDTH_AUTO)
          printf(" auto");
	else
          printf(" %.1f", style->background_position[j]);

      putchar('\n');
    }

    for (j = 0; j < 4; j ++)
      if (style->border[j].color_set ||
          style->border[j].style != HD_BORDER_STYLE_NONE ||
          style->border[j].width != HD_WIDTH_AUTO)
      {
	printf("  border-%s:", pos[j]);

	if (style->border[j].color_set == HD_COLOR_TRANSPARENT)
          fputs(" transparent", stdout);
	else if (style->border[j].color_set == HD_COLOR_SET)
	  printf(" rgb(%d,%d,%d)", style->border[j].color[0],
		 style->border[j].color[1], style->border[j].color[2]);

	printf(" %s", border_style[style->border[j].style]);

	if (style->border[j].width != HD_WIDTH_AUTO)
          printf(" %.1f\n", style->border[j].width);
	else
          putchar('\n');
      }

    if (style->selectors[0].element == HD_ELEMENT_TABLE)
      printf("  caption-side: %s\n", caption_side[style->caption_side]);

    if (style->clear != HD_CLEAR_NONE)
      printf("  clear: %s\n", clear[style->clear]);

    if (style->color_set == HD_COLOR_SET)
      printf("  color: rgb(%d,%d,%d)\n", style->color[0],
	     style->color[1], style->color[2]);

    if (style->display != HD_DISPLAY_INLINE)
      printf("  display: %s\n", display[style->display]);

    if (style->float_ != HD_FLOAT_NONE)
      printf("  float: %s\n", float_[style->float_]);

    if (style->font_family)
      printf("  font-family: %s\n", style->font_family);

    if (style->font_size_rel)
      printf("  font-size: %s (%.1f)\n", style->font_size_rel,
             style->font_size);
    else
      printf("  font-size: %.1f\n", style->font_size);

    if (style->font_style)
      printf("  font-style: %s\n", font_style[style->font_style]);

    if (style->font_variant)
      printf("  font-variant: %s\n", font_variant[style->font_variant]);

    if (style->font_weight)
      printf("  font-weight: %s\n", font_weight[style->font_weight]);

    if (style->line_height_rel)
      printf("  line-height: %s (%.1f)\n", style->line_height_rel,
             style->line_height);
    else
      printf("  line-height: %.1f\n", style->line_height);

    if (style->list_style_position != HD_LIST_STYLE_POSITION_INHERIT)
      printf("  list-style-position: %s\n",
             list_style_position[style->list_style_position]);

    if (style->list_style_type != HD_LIST_STYLE_TYPE_INHERIT)
      printf("  list-style-type: %s\n",
             list_style_type[style->list_style_type]);

    for (j = 0; j < 4; j ++)
      if (style->margin[j] != HD_WIDTH_AUTO || style->margin_rel[j])
      {
	printf("  margin-%s:", pos[j]);

        if (style->margin_rel[j])
	  printf(" %s (%.1f)\n", style->margin_rel[j], style->margin[j]);
	else
          printf(" %.1f\n", style->margin[j]);
      }

    for (j = 0; j < 4; j ++)
      if (style->padding[j] != HD_WIDTH_AUTO || style->padding_rel[j])
      {
	printf("  padding-%s:", pos[j]);

        if (style->padding_rel[j])
	  printf(" %s (%.1f)\n", style->padding_rel[j], style->padding[j]);
	else
          printf(" %.1f\n", style->padding[j]);
      }

    if (style->page_break_after)
      printf("  page-break-after: %s\n", page_break[style->page_break_after]);

    if (style->page_break_before)
      printf("  page-break-before: %s\n", page_break[style->page_break_before]);

    if (style->page_break_inside)
      printf("  page-break-inside: %s\n", page_break[style->page_break_inside]);

    if (style->text_align != HD_TEXT_ALIGN_INHERIT)
      printf("  text-align: %s\n", text_align[style->text_align]);

    if (style->text_decoration != HD_TEXT_DECORATION_INHERIT)
      printf("  text-decoration: %s\n", text_decoration[style->text_decoration]);

    if (style->text_transform != HD_TEXT_TRANSFORM_INHERIT)
      printf("  text-transform: %s\n", text_transform[style->text_transform]);

    if (style->vertical_align != HD_VERTICAL_ALIGN_INHERIT)
      printf("  vertical-align: %s\n", vertical_align[style->vertical_align]);

    if (style->white_space != HD_WHITE_SPACE_INHERIT)
      printf("  white-space: %s\n", white_space[style->white_space]);

    puts("}\n");
  }

  // Free memory and return...
  delete css;

  return (0);
}


//
// End of "$Id: teststyle.cxx,v 1.1.2.5 2005/05/07 03:02:38 mike Exp $".
//