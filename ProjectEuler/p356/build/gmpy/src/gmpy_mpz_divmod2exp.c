/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gmpy_mpz_divmod2exp.c                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Python interface to the GMP or MPIR, MPFR, and MPC multiple precision   *
 * libraries.                                                              *
 *      Copyright 2000 - 2009 Alex Martelli                                *
 *      Copyright 2008 - 2011 Case Van Horsen                              *
 *                                                                         *
 * This library is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU Lesser General Public License as published   *
 * by the Free Software Foundation; either version 2.1 of the License, or  *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * Lesser General Public License for more details.                         *
 *                                                                         *
 * You should have received a copy of the GNU Lesser General Public        *
 * License along with this library; if not, write to the Free Software     *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA           *
 * 02110-1301  USA                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


/* This file contains functions related to division and remainder by a power
 * of two.
 */

/*
 **************************************************************************
 * Ceiling division and remainder by power of two.
 **************************************************************************
 */

PyDoc_STRVAR(doc_gmpy_c_divmod_2exp,
"c_divmod_2exp(x,n): returns the quotient and remainder of x\n"
"divided by 2**n. The quotient is rounded towards +Inf (ceiling\n"
"rounding) and the remainder will be negative. x must be an\n"
"integer. n must be > 0.");
static PyObject *
Pygmpy_c_divmod_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x, *result;
    PympzObject *q, *r, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("c_divmod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("c_divmod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("c_divmod_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    CREATE_TWO_MPZ_TUPLE(q, r, result);

    if (CHECK_MPZANY(x)) {
        mpz_cdiv_q_2exp(q->z, Pympz_AS_MPZ(x), nbits);
        mpz_cdiv_r_2exp(r->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("c_divmod_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)q);
            Py_DECREF((PyObject*)r);
            Py_DECREF(result);
            return NULL;
        }
        mpz_cdiv_q_2exp(q->z, tempx->z, nbits);
        mpz_cdiv_r_2exp(r->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    PyTuple_SET_ITEM(result, 0, (PyObject*)q);
    PyTuple_SET_ITEM(result, 1, (PyObject*)r);
    return result;
}

PyDoc_STRVAR(doc_gmpy_c_div_2exp,
"c_div_2exp(x,n): returns the quotient of x divided by 2**n. The\n"
"quotient is rounded towards +Inf (ceiling rounding). x must be an\n"
"integer. n must be > 0.");
static PyObject *
Pygmpy_c_div_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x;
    PympzObject *result, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("c_div_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("c_div_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("c_div_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    if (!(result = Pympz_new()))
        return NULL;

    if (CHECK_MPZANY(x)) {
        mpz_cdiv_q_2exp(result->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("c_div_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)result);
            return NULL;
        }
        mpz_cdiv_q_2exp(result->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    return (PyObject*)result;
}

PyDoc_STRVAR(doc_gmpy_c_mod_2exp,
"c_mod_2exp(x,n): returns the remainder of x divided by 2**n. The\n"
"remainder will be negative. x must be an integer. n must be > 0.");
static PyObject *
Pygmpy_c_mod_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x;
    PympzObject *result, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("c_mod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("c_mod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("c_mod_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    if (!(result = Pympz_new()))
        return NULL;

    if (CHECK_MPZANY(x)) {
        mpz_cdiv_r_2exp(result->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("c_mod_2exp() requires expects 'mpz','int' arguments");
            Py_DECREF((PyObject*)result);
            return NULL;
        }
        mpz_cdiv_r_2exp(result->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    return (PyObject*)result;
}

/*
 **************************************************************************
 * Floor division and remainder by power of two.
 **************************************************************************
 */

PyDoc_STRVAR(doc_gmpy_f_divmod_2exp,
"f_divmod_2exp(x,n): returns quotient and remainder after dividing\n"
"x by 2**n. The quotient is rounded towards -Inf (floor rounding)\n"
"and the remainder will be positive. x must be an integer. n must\n"
"be > 0.");
static PyObject *
Pygmpy_f_divmod_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x, *result;
    PympzObject *q, *r, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("f_divmod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("f_divmod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("f_divmod_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    CREATE_TWO_MPZ_TUPLE(q, r, result);

    if (CHECK_MPZANY(x)) {
        mpz_fdiv_q_2exp(q->z, Pympz_AS_MPZ(x), nbits);
        mpz_fdiv_r_2exp(r->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("f_divmod_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)q);
            Py_DECREF((PyObject*)r);
            Py_DECREF(result);
            return NULL;
        }
        mpz_fdiv_q_2exp(q->z, tempx->z, nbits);
        mpz_fdiv_r_2exp(r->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    PyTuple_SET_ITEM(result, 0, (PyObject*)q);
    PyTuple_SET_ITEM(result, 1, (PyObject*)r);
    return result;
}

PyDoc_STRVAR(doc_gmpy_f_div_2exp,
"f_div_2exp(x,n): returns the quotient of x divided by 2**n. The\n"
"quotient is rounded towards -Inf (floor rounding). x must be an\n"
"integer. n must be > 0.");
static PyObject *
Pygmpy_f_div_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x;
    PympzObject *result, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("f_div_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("f_div_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("f_div_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    if (!(result = Pympz_new()))
        return NULL;

    if (CHECK_MPZANY(x)) {
        mpz_fdiv_q_2exp(result->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("f_div_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)result);
            return NULL;
        }
        mpz_fdiv_q_2exp(result->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    return (PyObject*)result;
}

PyDoc_STRVAR(doc_gmpy_f_mod_2exp,
"f_mod_2exp(x,n): returns remainder of x divided by 2**n. The\n"
"remainder will be positive. x must be an integer. n must be\n"
"greater than 0.");
static PyObject *
Pygmpy_f_mod_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x;
    PympzObject *result, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("f_mod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("f_mod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("f_mod_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    if (!(result = Pympz_new()))
        return NULL;

    if (CHECK_MPZANY(x)) {
        mpz_fdiv_r_2exp(result->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("f_mod_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)result);
            return NULL;
        }
        mpz_fdiv_r_2exp(result->z, Pympz_AS_MPZ(tempx), nbits);
        Py_DECREF((PyObject*)tempx);
    }
    return (PyObject*)result;
}

/*
 **************************************************************************
 * Truncating division and remainder by power of two.
 **************************************************************************
 */

PyDoc_STRVAR(doc_gmpy_t_divmod_2exp,
"t_divmod_2exp(x,n): returns the quotient and remainder of x divided\n"
"by 2**n. The quotient is rounded towards zero (truncation) and the\n"
"remainder will have the same sign as x. x must be an integer. n must\n"
"be > 0.");
static PyObject *
Pygmpy_t_divmod_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x, *result;
    PympzObject *q, *r, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("t_divmod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("t_divmod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("t_divmod_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    CREATE_TWO_MPZ_TUPLE(q, r, result);

    if (CHECK_MPZANY(x)) {
        mpz_tdiv_q_2exp(q->z, Pympz_AS_MPZ(x), nbits);
        mpz_tdiv_r_2exp(r->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("t_divmod_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)q);
            Py_DECREF((PyObject*)r);
            Py_DECREF(result);
            return NULL;
        }
        mpz_tdiv_q_2exp(q->z, tempx->z, nbits);
        mpz_tdiv_r_2exp(r->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    PyTuple_SET_ITEM(result, 0, (PyObject*)q);
    PyTuple_SET_ITEM(result, 1, (PyObject*)r);
    return result;
}

PyDoc_STRVAR(doc_gmpy_t_div_2exp,
"t_div_2exp(x,n): returns the quotient of x divided by 2**n. The\n"
"quotient is rounded towards zero (truncation). n must be > 0.");
static PyObject *
Pygmpy_t_div_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x;
    PympzObject *result, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("t_div_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("t_div_2exp() requires 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("t_div_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    if (!(result = Pympz_new()))
        return NULL;
    if (CHECK_MPZANY(x)) {
        mpz_tdiv_q_2exp(result->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("t_div_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)result);
            return NULL;
        }
        mpz_tdiv_q_2exp(result->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    return (PyObject*)result;
}

PyDoc_STRVAR(doc_gmpy_t_mod_2exp,
"t_mod_2exp(x,n): returns the remainder of x divided by 2**n. The\n"
"remainder will have the same sign as x. x must be an integer. n\n"
"must be > 0.");
static PyObject *
Pygmpy_t_mod_2exp(PyObject *self, PyObject *args)
{
    long nbits;
    PyObject *x;
    PympzObject *result, *tempx;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("t_mod_2exp() requires 'mpz','int' arguments");
        return NULL;
    }

    nbits = clong_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("t_mod_2exp() requires expects 'mpz','int' arguments");
        return NULL;
    }
    if (nbits <= 0) {
        VALUE_ERROR("t_mod_2exp() requires n > 0");
        return NULL;
    }

    x = PyTuple_GET_ITEM(args, 0);
    if (!(result = Pympz_new()))
        return NULL;

    if (CHECK_MPZANY(x)) {
        mpz_tdiv_r_2exp(result->z, Pympz_AS_MPZ(x), nbits);
    }
    else {
        if (!(tempx = Pympz_From_Integer(x))) {
            TYPE_ERROR("t_mod_2exp() requires 'mpz','int' arguments");
            Py_DECREF((PyObject*)result);
            return NULL;
        }
        mpz_tdiv_r_2exp(result->z, tempx->z, nbits);
        Py_DECREF((PyObject*)tempx);
    }
    return (PyObject*)result;
}

/*
 **************************************************************************
 * pack and unpack methods
 *
 * Both pack and unpack use a devious trick when stuffing values into the
 * internal structure of an mpz_t. By setting a bit beyond the range of
 * interest, we are guaranteed that memory will remain available. When
 * the bit is cleared, it also triggers normalization of the value by
 * accounting for leading bits that are zero.
 **************************************************************************
 */

PyDoc_STRVAR(doc_gmpy_pack,
"pack(l,n): packs a list of integers 'l' into a single 'mpz' by\n"
"concatenating each integer after padding to length n bits. Raises\n"
"an error if any integer is negative or greater than n bits in\n"
"length.");
static PyObject *
Pygmpy_pack(PyObject *self, PyObject *args)
{
    Py_ssize_t nbits, total_bits, index, lst_count, i, temp_bits, limb_count, tempx_bits;
    PyObject *lst;
    mpz_t temp;
    PympzObject *result, *tempx = 0;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("pack() requires 'list','int' arguments");
        return NULL;
    }

    nbits = ssize_t_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("pack() requires 'list','int' arguments");
        return NULL;
    }

    if (nbits <= 0) {
        VALUE_ERROR("pack() requires n > 0");
        return NULL;
    }

    if (!PyList_Check(PyTuple_GET_ITEM(args, 0))) {
        TYPE_ERROR("pack() requires 'list','int' arguments");
        return NULL;
    }

    if (!(result = Pympz_new()))
        return NULL;

    lst = PyTuple_GET_ITEM(args, 0);
    lst_count = PyList_GET_SIZE(lst);
    total_bits = nbits * lst_count;

    mpz_set_ui(result->z, 0);
    mpz_setbit(result->z, total_bits + (mp_bits_per_limb * 2));

    mpz_inoc(temp);
    mpz_set_ui(temp, 0);
    limb_count = 0;
    tempx_bits = 0;

    for (index = 0; index < lst_count; index++) {
        if (!(tempx = Pympz_From_Integer(PyList_GetItem(lst, index)))
            || (mpz_sgn(tempx->z) < 0)
            || (mpz_sizeinbase(tempx->z,2) > (size_t)nbits)) {
            TYPE_ERROR("pack() requires list elements be positive integers < 2^nbits");
            mpz_cloc(temp);
            Py_XDECREF((PyObject*)tempx);
            Py_DECREF((PyObject*)result);
            return NULL;
        }
        mpz_mul_2exp(tempx->z, tempx->z, tempx_bits);
        mpz_add(temp, temp, tempx->z);
        tempx_bits += nbits;
        i = 0;
        temp_bits = mpz_sizeinbase(temp, 2) * mpz_sgn(temp);
        while (tempx_bits >= mp_bits_per_limb) {
            if (temp_bits > 0) {
                result->z->_mp_d[limb_count] = mpz_getlimbn(temp, i);
            }
            i += 1;
            tempx_bits -= mp_bits_per_limb;
            limb_count += 1;
            temp_bits -= mp_bits_per_limb;
        }
        if (temp_bits > 0) {
            mpz_tdiv_q_2exp(temp, temp, mp_bits_per_limb * i);
        }
        else {
            mpz_set_ui(temp, 0);
        }
        Py_DECREF((PyObject*)tempx);
    }
    result->z->_mp_d[limb_count] = mpz_getlimbn(temp, 0);
    mpz_clrbit(result->z, total_bits + (mp_bits_per_limb * 2));
    mpz_cloc(temp);
    return (PyObject*)result;
}

PyDoc_STRVAR(doc_gmpy_unpack,
"unpack(x,n): unpacks an integer 'x' into a list of n-bit values.\n"
"Raises error if 'x' is negative.");
static PyObject *
Pygmpy_unpack(PyObject *self, PyObject *args)
{
    Py_ssize_t nbits, total_bits, index = 0, lst_count, i, temp_bits = 0, extra_bits = 0;
    Py_ssize_t guard_bit, lst_ptr = 0;
    PyObject *result;
    mpz_t temp;
    mp_limb_t extra = 0;
    PympzObject *item, *tempx = 0;

    if (PyTuple_GET_SIZE(args) != 2) {
        TYPE_ERROR("unpack() requires 'int','int' arguments");
        return NULL;
    }

    nbits = ssize_t_From_Integer(PyTuple_GET_ITEM(args, 1));
    if (nbits == -1 && PyErr_Occurred()) {
        TYPE_ERROR("unpack() requires 'int','int' arguments");
        return NULL;
    }

    if (nbits <= 0) {
        VALUE_ERROR("unpack() requires n > 0");
        return NULL;
    }

    if (!(tempx = Pympz_From_Integer(PyTuple_GET_ITEM(args, 0)))) {
        TYPE_ERROR("unpack() requires 'int','int' arguments");
        return NULL;
    }

    total_bits = mpz_sizeinbase(tempx->z, 2) * mpz_sgn(tempx->z);
    lst_count = total_bits / nbits;
    if ((total_bits % nbits) || !lst_count)
        lst_count += 1;

    if (!(result = PyList_New(lst_count))) {
        Py_DECREF((PyObject*)tempx);
        return NULL;
    }

    if (mpz_sgn(tempx->z) == 0) {
        if (!(item = Pympz_new())) {
            Py_DECREF((PyObject*)tempx);
            Py_DECREF(result);
            return NULL;
        }
        mpz_set_ui(item->z, 0);
        PyList_SET_ITEM(result, 0, (PyObject*)item);
        Py_DECREF((PyObject*)tempx);
        return result;
    }

    mpz_inoc(temp);
    guard_bit = nbits + (2 * mp_bits_per_limb);

    while (lst_ptr < lst_count) {
        i = 0;
        temp_bits = 0;
        mpz_set_ui(temp, 0);
        mpz_setbit(temp, guard_bit);
        while (temp_bits + extra_bits < nbits) {
            temp->_mp_d[i++] = mpz_getlimbn(tempx->z, index++);
            temp_bits += mp_bits_per_limb;
        }
        mpz_clrbit(temp, guard_bit);
        mpz_mul_2exp(temp, temp, extra_bits);
        if (mpz_sgn(temp) == 0) {
            mpz_set_ui(temp, 1);
            temp->_mp_d[0] = extra;
        }
        else {
           mpn_add_1(temp->_mp_d, temp->_mp_d, mpz_size(temp), extra);
        }
        temp_bits += extra_bits;

        while ((lst_ptr < lst_count) && (temp_bits >= nbits)) {
            if(!(item = Pympz_new())) {
                mpz_cloc(temp);
                Py_DECREF((PyObject*)tempx);
                Py_DECREF(result);
                return NULL;
            }
            mpz_tdiv_r_2exp(item->z, temp, nbits);
            PyList_SET_ITEM(result, lst_ptr++, (PyObject*)item);
            mpz_tdiv_q_2exp(temp, temp, nbits);
            temp_bits -= nbits;
        }
        extra = mpz_getlimbn(temp, 0);
        extra_bits = temp_bits;
    }
    Py_DECREF((PyObject*)tempx);
    mpz_cloc(temp);
    return result;
}


