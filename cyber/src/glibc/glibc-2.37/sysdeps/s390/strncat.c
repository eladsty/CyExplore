/* Multiple versions of strncat.
   Copyright (C) 2015-2023 Free Software Foundation, Inc.
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
   <https://www.gnu.org/licenses/>.  */

#include <ifunc-strncat.h>

#if HAVE_STRNCAT_IFUNC
# include <string.h>
# include <ifunc-resolve.h>

# if HAVE_STRNCAT_C
extern __typeof (__strncat) STRNCAT_C attribute_hidden;
# endif

# if HAVE_STRNCAT_Z13
extern __typeof (__strncat) STRNCAT_Z13 attribute_hidden;
# endif

s390_libc_ifunc_expr (__strncat, strncat,
		      (HAVE_STRNCAT_Z13 && (hwcap & HWCAP_S390_VX))
		      ? STRNCAT_Z13
		      : STRNCAT_DEFAULT
		      )
#endif