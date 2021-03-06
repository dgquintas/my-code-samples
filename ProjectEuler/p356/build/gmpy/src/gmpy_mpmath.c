/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gmpy_mpmath.c                                                           *
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


/* Internal helper function for mpmath. */

static PyObject *
mpmath_build_mpf(long sign, PympzObject *man, PyObject *exp, long bc)
{
    PyObject *tup, *tsign, *tbc;
    if(!(tup = PyTuple_New(4))){
        Py_DECREF((PyObject*)man);
        Py_DECREF(exp);
        return NULL;
    }
    if(!(tsign=PyIntOrLong_FromLong(sign))){
        Py_DECREF((PyObject*)man);
        Py_DECREF(exp);
        Py_DECREF(tup);
        return NULL;
    }
    if(!(tbc=PyIntOrLong_FromLong(bc))){
        Py_DECREF((PyObject*)man);
        Py_DECREF(exp);
        Py_DECREF(tup);
        Py_DECREF(tsign);
        return NULL;
    }
    PyTuple_SET_ITEM(tup, 0, tsign);
    PyTuple_SET_ITEM(tup, 1, (PyObject*)man);
    PyTuple_SET_ITEM(tup, 2, (exp)?exp:PyIntOrLong_FromLong(0));
    PyTuple_SET_ITEM(tup, 3, tbc);
    return tup;
}

static PympzObject *
Pympz_FROM_MPZ(mpz_t z)
{
    PympzObject *self;

    if(!(self = PyObject_New(PympzObject, &Pympz_Type)))
        return NULL;
    self->z[0] = z[0];
    return self;
}

static char doc_mpmath_normalizeg[]="\
_mpmath_normalize(...): helper function for mpmath.\n\
";
static PyObject *
Pympz_mpmath_normalize(PyObject *self, PyObject *args)
{
    long sign = 0, bc = 0, prec = 0, shift, zbits, carry = 0;
    PyObject *exp = 0, *newexp = 0, *newexp2 = 0, *tmp = 0;
    PympzObject *man = 0;
    mpz_t upper, lower;
    char rnd = 0;

    if(PyTuple_GET_SIZE(args) == 6){
        /* Need better error-checking here. Under Python 3.0, overflow into
           C-long is possible. */
        sign = clong_From_Integer(PyTuple_GET_ITEM(args, 0));
        man = (PympzObject *)PyTuple_GET_ITEM(args, 1);
        exp = PyTuple_GET_ITEM(args, 2);
        bc = clong_From_Integer(PyTuple_GET_ITEM(args, 3));
        prec = clong_From_Integer(PyTuple_GET_ITEM(args, 4));
        rnd = Py2or3String_AsString(PyTuple_GET_ITEM(args, 5))[0];
        if(PyErr_Occurred()){
            PyErr_SetString(PyExc_TypeError, "arguments long, PympzObject*,"
                "PyObject*, long, long, char needed");
            return NULL;
        }
    } else {
        PyErr_SetString(PyExc_TypeError, "6 arguments required");
        return NULL;
    }
    if(!Pympz_Check(man)){
        PyErr_SetString(PyExc_TypeError, "argument is not an mpz");
        return NULL;
    }

    /* If the mantissa is 0, return the normalized representation. */
    if(!mpz_sgn(man->z)) {
        Py_INCREF((PyObject*)man);
        return mpmath_build_mpf(0, man, 0, 0);
    }

    /* if bc <= prec and the number is odd return it */
    if ((bc <= prec) && mpz_odd_p(man->z)) {
        Py_INCREF((PyObject*)man);
        Py_INCREF((PyObject*)exp);
        return mpmath_build_mpf(sign, man, exp, bc);
    }

    mpz_inoc(upper);
    mpz_inoc(lower);

    shift = bc - prec;
    if(shift>0) {
        switch(rnd) {
            case 'f':
                if(sign) {
                    mpz_cdiv_q_2exp(upper, man->z, shift);
                } else {
                    mpz_fdiv_q_2exp(upper, man->z, shift);
                }
                break;
            case 'c':
                if(sign) {
                    mpz_fdiv_q_2exp(upper, man->z, shift);
                } else {
                    mpz_cdiv_q_2exp(upper, man->z, shift);
                }
                break;
            case 'd':
                mpz_fdiv_q_2exp(upper, man->z, shift);
                break;
            case 'u':
                mpz_cdiv_q_2exp(upper, man->z, shift);
                break;
            case 'n':
            default:
                mpz_tdiv_r_2exp(lower, man->z, shift);
                mpz_tdiv_q_2exp(upper, man->z, shift);
                if(mpz_sgn(lower)) {
                    /* lower is not 0 so it must have at least 1 bit set */
                    if(mpz_sizeinbase(lower, 2)==shift) {
                        /* lower is >= 1/2 */
                        if(mpz_scan1(lower, 0)==shift-1) {
                            /* lower is exactly 1/2 */
                            if(mpz_odd_p(upper))
                                carry = 1;
                        } else {
                            carry = 1;
                        }
                    }
                }
                if(carry)
                    mpz_add_ui(upper, upper, 1);
        }
        if (!(tmp = PyIntOrLong_FromLong(shift))) {
            mpz_cloc(upper);
            mpz_cloc(lower);
            return NULL;
        }
        if (!(newexp = PyNumber_Add(exp, tmp))) {
            mpz_cloc(upper);
            mpz_cloc(lower);
            Py_DECREF(tmp);
            return NULL;
        }
        Py_DECREF(tmp);
        bc = prec;
    } else {
        mpz_set(upper, man->z);
        newexp = exp;
        Py_INCREF(newexp);
    }

    /* Strip trailing 0 bits. */
    if((zbits = mpz_scan1(upper, 0)))
        mpz_tdiv_q_2exp(upper, upper, zbits);

    if (!(tmp = PyIntOrLong_FromLong(zbits))) {
        mpz_cloc(upper);
        mpz_cloc(lower);
        Py_DECREF(newexp);
        return NULL;
    }
    if (!(newexp2 = PyNumber_Add(newexp, tmp))) {
        mpz_cloc(upper);
        mpz_cloc(lower);
        Py_DECREF(tmp);
        Py_DECREF(newexp);
        return NULL;
    }
    Py_DECREF(newexp);
    Py_DECREF(tmp);

    bc -= zbits;
    /* Check if one less than a power of 2 was rounded up. */
    if(!mpz_cmp_ui(upper, 1))
        bc = 1;

    mpz_cloc(lower);
    return mpmath_build_mpf(sign, Pympz_FROM_MPZ(upper), newexp2, bc);
}

static char doc_mpmath_createg[]="\
_mpmath_create(...): helper function for mpmath.\n\
";
static PyObject *
Pympz_mpmath_create(PyObject *self, PyObject *args)
{
    long sign, bc, shift, zbits, carry = 0;
    PyObject *exp = 0, *newexp = 0, *newexp2 = 0, *tmp = 0;
    PympzObject *man = 0, *upper = 0, *lower = 0;

    const char *rnd = "f";
    long prec = 0;

    if(PyTuple_GET_SIZE(args) < 2) {
        PyErr_SetString(PyExc_TypeError,
                "mpmath_create() expects 'mpz','int'[,'int','str'] arguments");
        return NULL;
    }

    switch(PyTuple_GET_SIZE(args)) {
        case 4:
            rnd = Py2or3String_AsString(PyTuple_GET_ITEM(args, 3));
        case 3:
            prec = clong_From_Integer(PyTuple_GET_ITEM(args, 2));
            if(prec == -1 && PyErr_Occurred())
                return NULL;
            prec = abs(prec);
        case 2:
            exp = PyTuple_GET_ITEM(args, 1);
        case 1:
            man = Pympz_From_Integer(PyTuple_GET_ITEM(args, 0));
            if(!man) {
                PyErr_SetString(PyExc_TypeError,
                        "mpmath_create() expects 'mpz','int'[,'int','str'] arguments");
                return NULL;
            }
    }

    /* If the mantissa is 0, return the normalized representation. */
    if(!mpz_sgn(man->z)) {
        return mpmath_build_mpf(0, man, 0, 0);
    }

    upper = Pympz_new();
    lower = Pympz_new();
    if(!upper||!lower) {
        Py_DECREF((PyObject*)man);
        Py_XDECREF((PyObject*)upper);
        Py_XDECREF((PyObject*)lower);
        return NULL;
    }

    /* Extract sign, make man positive, and set bit count */
    sign = (mpz_sgn(man->z) == -1);
    mpz_abs(upper->z, man->z);
    bc = mpz_sizeinbase(upper->z, 2);

    if(!prec) prec = bc;

    shift = bc - prec;
    if(shift>0) {
        switch(rnd[0]) {
            case 'f':
                if(sign) {
                    mpz_cdiv_q_2exp(upper->z, upper->z, shift);
                } else {
                    mpz_fdiv_q_2exp(upper->z, upper->z, shift);
                }
                break;
            case 'c':
                if(sign) {
                    mpz_fdiv_q_2exp(upper->z, upper->z, shift);
                } else {
                    mpz_cdiv_q_2exp(upper->z, upper->z, shift);
                }
                break;
            case 'd':
                mpz_fdiv_q_2exp(upper->z, upper->z, shift);
                break;
            case 'u':
                mpz_cdiv_q_2exp(upper->z, upper->z, shift);
                break;
            case 'n':
            default:
                mpz_tdiv_r_2exp(lower->z, upper->z, shift);
                mpz_tdiv_q_2exp(upper->z, upper->z, shift);
                if(mpz_sgn(lower->z)) {
                    /* lower is not 0 so it must have at least 1 bit set */
                    if(mpz_sizeinbase(lower->z, 2)==shift) {
                        /* lower is >= 1/2 */
                        if(mpz_scan1(lower->z, 0)==shift-1) {
                            /* lower is exactly 1/2 */
                            if(mpz_odd_p(upper->z))
                                carry = 1;
                        } else {
                            carry = 1;
                        }
                    }
                }
                if(carry)
                    mpz_add_ui(upper->z, upper->z, 1);
        }
        if (!(tmp = PyIntOrLong_FromLong(shift))) {
            Py_DECREF((PyObject*)upper);
            Py_DECREF((PyObject*)lower);
            return NULL;
        }
        if (!(newexp = PyNumber_Add(exp, tmp))) {
            Py_DECREF((PyObject*)man);
            Py_DECREF((PyObject*)upper);
            Py_DECREF((PyObject*)lower);
            Py_DECREF(tmp);
            return NULL;
        }
        Py_DECREF(tmp);
        bc = prec;
    } else {
        newexp = exp;
        Py_INCREF(newexp);
    }

    /* Strip trailing 0 bits. */
    if((zbits = mpz_scan1(upper->z, 0)))
        mpz_tdiv_q_2exp(upper->z, upper->z, zbits);

    if (!(tmp = PyIntOrLong_FromLong(zbits))) {
        Py_DECREF((PyObject*)man);
        Py_DECREF((PyObject*)upper);
        Py_DECREF((PyObject*)lower);
        Py_DECREF(newexp);
        return NULL;
    }
    if (!(newexp2 = PyNumber_Add(newexp, tmp))) {
        Py_DECREF((PyObject*)man);
        Py_DECREF((PyObject*)upper);
        Py_DECREF((PyObject*)lower);
        Py_DECREF(tmp);
        Py_DECREF(newexp);
        return NULL;
    }
    Py_DECREF(newexp);
    Py_DECREF(tmp);

    bc -= zbits;
    /* Check if one less than a power of 2 was rounded up. */
    if(!mpz_cmp_ui(upper->z, 1))
        bc = 1;

    Py_DECREF((PyObject*)lower);
    Py_DECREF((PyObject*)man);
    return mpmath_build_mpf(sign, upper, newexp2, bc);
}
