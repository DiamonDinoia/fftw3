/*
 * Copyright (c) 2002 Matteo Frigo
 * Copyright (c) 2002 Steven G. Johnson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "api.h"

typedef struct {
     scanner super;
     const char *s;
} S_str;

static int getchr_str(scanner *sc_)
{
     S_str *sc = (S_str *) sc_;
     if (!*sc->s)
	  return EOF;
     return *sc->s++;
}

scanner *X(mkscanner_str)(const char *s)
{
     S_str *sc = (S_str *) X(mkscanner)(sizeof(S_str), getchr_str);
     sc->s = s;
     return &sc->super;
}

int X(import_wisdom_from_string)(const char *input_string)
{
     scanner *s = X(mkscanner_str)(input_string);
     planner *plnr = X(the_planner)();
     int ret = plnr->adt->imprt(plnr, s);
     X(scanner_destroy)(s);
     return ret;
}
