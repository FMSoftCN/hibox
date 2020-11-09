/**
 * The MIT License (MIT)
 * Copyright (c) 2009-2016 Gerardo Orellana <hello @ goaccess.io>
 * Copyright (c) 2020 FMSoft <https://www.fmsoft.cn>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef HIBOX_GSLIST_H
#define HIBOX_GSLIST_H

/* Generic Single linked-list */
typedef struct GSLList_
{
  void *data;
  struct GSLList_ *next;
} GSLList;

#ifdef __cplusplus
extern "C" {
#endif

/* single linked-list */
GSLList *gslist_create (void *data);
GSLList *gslist_find (GSLList * node, int (*func) (void *, void *), void *data);
GSLList *gslist_insert_append (GSLList * node, void *data);
GSLList *gslist_insert_prepend (GSLList * list, void *data);
int gslist_count (GSLList * list);
int gslist_foreach (GSLList * node, int (*func) (void *, void *),
                  void *user_data);
int gslist_remove_node (GSLList ** list, GSLList * node);
int gslist_remove_nodes (GSLList * list);

#ifdef __cplusplus
}
#endif

#endif // HIBOX_GSLIST_H
