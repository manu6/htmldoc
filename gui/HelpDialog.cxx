// generated by Fast Light User Interface Designer (fluid) version 1.00

#include "HelpDialog.h"

inline void HelpDialog::cb_view__i(HelpView*, void*) {
  if (view_->changed())
{
  index_ ++;

  if (index_ >= 100)
  {
    memcpy(line_, line_ + 10, sizeof(line_[0]) * 90);
    memcpy(file_, file_ + 10, sizeof(file_[0]) * 90);
    index_ -= 10;
  }

  max_ = index_;

  strcpy(file_[index_], view_->filename());
  line_[index_] = view_->topline();

  if (index_ > 0)
    back_->activate();
  else
    back_->deactivate();

  forward_->deactivate();
}
else if (view_->filename())
{
  strncpy(file_[index_], view_->filename(), 255);
  file_[index_][255] = '\0';
  line_[index_] = view_->topline();
};
}
void HelpDialog::cb_view_(HelpView* o, void* v) {
  ((HelpDialog*)(o->parent()->user_data()))->cb_view__i(o,v);
}

inline void HelpDialog::cb_Close_i(Fl_Button*, void*) {
  window_->hide();
}
void HelpDialog::cb_Close(Fl_Button* o, void* v) {
  ((HelpDialog*)(o->parent()->user_data()))->cb_Close_i(o,v);
}

inline void HelpDialog::cb_back__i(Fl_Button*, void*) {
  if (index_ > 0)
  index_ --;

if (index_ == 0)
  back_->deactivate();

forward_->activate();

if (strcmp(view_->filename(), file_[index_]) != 0)
  view_->load(file_[index_]);

view_->topline(line_[index_]);
}
void HelpDialog::cb_back_(Fl_Button* o, void* v) {
  ((HelpDialog*)(o->parent()->user_data()))->cb_back__i(o,v);
}

inline void HelpDialog::cb_forward__i(Fl_Button*, void*) {
  if (index_ < max_)
  index_ ++;

if (index_ >= max_)
  forward_->deactivate();

back_->activate();

if (strcmp(view_->filename(), file_[index_]) != 0)
  view_->load(file_[index_]);

view_->topline(line_[index_]);
}
void HelpDialog::cb_forward_(Fl_Button* o, void* v) {
  ((HelpDialog*)(o->parent()->user_data()))->cb_forward__i(o,v);
}

HelpDialog::HelpDialog() {
  Fl_Window* w;
  { Fl_Window* o = window_ = new Fl_Window(530, 385, "Help Dialog");
    w = o;
    o->user_data((void*)(this));
    { HelpView* o = view_ = new HelpView(10, 10, 510, 330);
      o->box(FL_DOWN_BOX);
      o->callback((Fl_Callback*)cb_view_);
      o->end();
      Fl_Group::current()->resizable(o);
    }
    { Fl_Button* o = new Fl_Button(465, 350, 55, 25, "Close");
      o->callback((Fl_Callback*)cb_Close);
    }
    { Fl_Button* o = back_ = new Fl_Button(395, 350, 25, 25, "@<");
      o->shortcut(0xff51);
      o->labeltype(FL_SYMBOL_LABEL);
      o->callback((Fl_Callback*)cb_back_);
    }
    { Fl_Button* o = forward_ = new Fl_Button(430, 350, 25, 25, "@>");
      o->shortcut(0xff53);
      o->labeltype(FL_SYMBOL_LABEL);
      o->callback((Fl_Callback*)cb_forward_);
    }
    o->end();
  }
  back_->deactivate();
forward_->deactivate();

index_ = 0;
max_  = 0;
}

void HelpDialog::hide() {
  window_->hide();
}

void HelpDialog::load(const char *f) {
  view_->load(f);
}

void HelpDialog::show() {
  window_->show();
}

void HelpDialog::topline(const char *n) {
  view_->topline(n);
}

void HelpDialog::topline(int n) {
  view_->topline(n);
}

int HelpDialog::visible() {
  return (window_->visible());
}
