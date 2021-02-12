#include "ts_iz_ext.h"
#include "scheme-private.h"
#include "scheme.h"

void ts_register_int_consts(scheme *sc, pointer env,
                            ts_registerable_int_const *list, int count) {
  int i;

  for (i = 0; i < count; i++) {
    pointer scm_c = mk_integer(sc, list[i].c);

    setimmutable(scm_c);

    scheme_define(sc, env, mk_symbol(sc, list[i].name), scm_c);
  }
}

pointer ts_mk_userdata(scheme *sc, void *ptr) {
  pointer cell = get_cell(sc, sc->NIL, sc->NIL);

  typeflag(cell) = (T_USERDATA | T_ATOM);
  cell->_object._userdata.ptr = ptr;

  return cell;
}

void ts_set_userdata_type(pointer userdata, int type) {
  userdata->_object._userdata.type = type;
}

int ts_userdata_type(pointer userdata) {
  return userdata->_object._userdata.type;
}

int ts_is_userdata(pointer ptr) { return type(ptr) == T_USERDATA; }

void *ts_userdata_ptr(pointer userdata) {
  return userdata->_object._userdata.ptr;
}

pointer ts_err(scheme *sc, const char *text) {
  _Error_1(sc, text, 0);
  Eval_Cycle(sc, sc->op);

  return _s_return(sc, sc->F);
}

pointer ts_arg_type_err(scheme *sc, const char *fn_name, int arg_num,
                        const char *expected_type) {
  char buff[STRBUFFSIZE];

  snprintf(buff, sizeof(buff), "%s: argument %d must be: %s", fn_name, arg_num,
           expected_type);

  return ts_err(sc, buff);
}

pointer ts_args_num_err(scheme *sc, const char *fn_name, int args_num) {
  char buff[STRBUFFSIZE];

  snprintf(buff, sizeof(buff), "%s: needs %d argument(s)", fn_name, args_num);

  return ts_err(sc, buff);
}

ts_status ts_load_file(scheme *sc, const char *path) {
  int status;
  FILE *file = fopen(path, "r");

  if (file == NULL) {
    return TS_FOPEN_ERR;
  }

  scheme_load_named_file(sc, file, path);

  status = fclose(file);

  if (status != 0) {
    return TS_FCLOSE_ERR;
  }

  return TS_OK;
}

pointer ts_sym_to_val(scheme *sc, pointer env, const char *name) {
  pointer sym = mk_symbol(sc, name);
  pointer slot = find_slot_in_env(sc, env, sym, 0);

  return slot_value_in_env(slot);
}

int ts_bool_val(scheme *sc, pointer obj) {
  if (obj == sc->F) {
    return 0;
  }

  return 1;
}

pointer ts_mk_bool(scheme *sc, int b) {
  if (b) {
    return sc->T;
  }

  return sc->F;
}

