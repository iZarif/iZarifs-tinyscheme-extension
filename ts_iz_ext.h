#ifndef TS_IZ_EXT_H
#define TS_IZ_EXT_H

#include "scheme.h"

typedef enum ts_status {
  TS_OK = 0,
  TS_FOPEN_ERR = -2,
  TS_FCLOSE_ERR = -3,
} ts_status;

typedef struct ts_registerable_int_const {
  int c;
  const char *name;
} ts_registerable_int_const;

void ts_register_int_consts(scheme *sc, pointer env,
                            ts_registerable_int_const *list, int count);
pointer ts_mk_userdata(scheme *sc, void *ptr);
void ts_set_userdata_type(pointer userdata, int type);
int ts_userdata_type(pointer userdata);
int ts_is_userdata(pointer ptr);
void *ts_userdata_ptr(pointer userdata);
pointer ts_err(scheme *sc, const char *text);
pointer ts_arg_type_err(scheme *sc, const char *fn_name, int arg_num,
                        const char *expected_type);
pointer ts_args_num_err(scheme *sc, const char *fn_name, int args_num);
ts_status ts_load_file(scheme *sc, const char *path);
pointer ts_sym_to_val(scheme *sc, pointer env, const char *name);
int ts_bool_val(scheme *sc, pointer obj);
pointer ts_mk_bool(scheme *sc, int b);

#endif
