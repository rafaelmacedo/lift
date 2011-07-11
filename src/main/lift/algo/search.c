/* Copyright (c) 2011, Diego Souza                                                 */
/* All rights reserved.                                                            */
                                                                                   
/* Redistribution and use in source and binary forms, with or without              */
/* modification, are permitted provided that the following conditions are met:     */
                                                                                   
/*   * Redistributions of source code must retain the above copyright notice,      */
/*     this list of conditions and the following disclaimer.                       */
/*   * Redistributions in binary form must reproduce the above copyright notice,   */
/*     this list of conditions and the following disclaimer in the documentation   */
/*     and/or other materials provided with the distribution.                      */
/*   * Neither the name of the <ORGANIZATION> nor the names of its contributors    */
/*     may be used to endorse or promote products derived from this software       */
/*     without specific prior written permission.                                  */

/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND */
/* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE    */
/* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL      */
/* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR      */
/* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      */
/* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */

#include <lift/algo/search.h>

static
bool __is_least(const gvalue_t *a, const gvalue_t *b)
{
  if (a == NULL)
    return(false);
  if (b == NULL)
    return(true);
  else
    return(gvalue_compare(a, b) == LT);
}

static
bool __is_greatest(const gvalue_t *a, const gvalue_t *b)
{
  if (a == NULL)
    return(false);
  if (b == NULL)
    return(true);
  else
    return(gvalue_compare(a, b) == GT);
}

static inline
list_node_t *__find_elem(const list_t *l, list_node_t *start, list_node_t *end, bool (*f)(const gvalue_t *, const gvalue_t *))
{
  gvalue_t *tmp_a, *tmp_b;
  list_node_t *found = NULL;

  while (start!=NULL)
  {
    tmp_a = (found==NULL ? NULL : list_get_data(l, found));
    tmp_b = list_get_data(l, start);
    found = (f(tmp_a, tmp_b) ? found : start);

    if (start == end)
      break;
    else
      start = list_next(l, start);
  }

  return(found);
}

int binary_search(const list_t *xs, const gvalue_t *x)
{
  int low  = 0;
  int high = list_size(xs);
  int mid, cmp;
  list_node_t *tmp;

  if (high == 0)
    return(NOT_FOUND);

  while (low<=high)
  {
    mid = low + ((high-low) >> 1);
    tmp = list_at(xs, mid);
    cmp = gvalue_compare(x, list_get_data(xs, tmp));

    if (cmp == EQ)
      return(mid);
    else if (cmp == LT)
      high = mid - 1;
    else /* if (cmp == GT) */
      low = mid + 1;
  }

  return(NOT_FOUND);
}

list_node_t *least_elem(const list_t *l, list_node_t *start, list_node_t *end)
{
  return(__find_elem(l, start, end, __is_least));
}

list_node_t *greatest_elem(const list_t *l, list_node_t *start, list_node_t *end)
{
  return(__find_elem(l, start, end, __is_greatest));
}
