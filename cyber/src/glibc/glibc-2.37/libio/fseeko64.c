/* Copyright (C) 1993-2023 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */

#include <errno.h>
#include "libioP.h"
#include "stdio.h"

/* fseeko.c defines this as an alias if __OFF_T_MATCHES_OFF64_T.  */
#ifndef __OFF_T_MATCHES_OFF64_T

int
__fseeko64 (FILE *fp, off64_t offset, int whence)
{
  int result;
  CHECK_FILE (fp, -1);
  _IO_acquire_lock (fp);
  result = _IO_fseek (fp, offset, whence);
  _IO_release_lock (fp);
  return result;
}
libc_hidden_def (__fseeko64)
weak_alias (__fseeko64, fseeko64)
#endif
