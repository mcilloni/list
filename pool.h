/*
 *  This file is part of First Step.
 *  
 *  First Step is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software 
 *  Foundation, either version 3 of the License, or (at your option) any later version. 
 *
 *  First Step is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with First Step.  If not, see <http://www.gnu.org/licenses/>
 *
 *  Copyright (C) Marco Cilloni <marco.cilloni@yahoo.com> 2014
 *
 */

//this ugly, not thread safe and should not be used by anyone. But it works, so who cares?
//the reason is, type structures are too often passed from a location to another, and this is also true for tokens and other structures. 
//This list preserves them, allowing to deallocate them easily after.

#if !defined(_POOL_H)
#define _POOL_H

#include "list.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef List Pool;

extern Pool* (*pool_new)(void);

void* pool_alloc(Pool *pool, size_t size);
void* pool_zalloc(Pool *pool, size_t size);

extern void (*pool_release)(Pool *pool, void (*freefunc)(void*));

#if defined(__cplusplus)
}
#endif

#endif
