/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * gmpy_basic.c                                                            *
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

/* Generic arithmetic methods for gmpy types.
 * The routines are highly optimized for performance.
 */

#include <math.h>

/* Generic addition
 *
 * Support addition for gmpy types with automatic conversion of Python types.
 *
 * The following conversion logic is used:
 *  1) 'mpz' combined with an integer type returns an 'mpz'
 *  2) 'mpz' combined with a rational type returns an 'mpq'
 *  3) 'mpz' combined with a floating-point type returns an 'mpf'
 *  4) 'mpq' combined with an integer or rational type returns an 'mpq'
 *  5) 'mpq' combines with a floating-point type returns an 'mpf'
 *
 * The most common inputs are processed as efficiently as possible.
 */

static PyObject *
Pympany_add(PyObject *a, PyObject *b)
{
    mpz_t tempz;
    PympzObject *rz = 0, *paz = 0, *pbz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *rf = 0, *paf = 0, *pbf = 0;
#else
    double tempdouble;
#endif
    long temp;
    int overflow;

    if (CHECK_MPZANY(a)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(b)) {
            TRACE("Adding (mpz,integer)\n");
            temp = PyLong_AsLongAndOverflow(b, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, b);
                mpz_add(rz->z, Pympz_AS_MPZ(a), tempz);
                mpz_cloc(tempz);
            }
            else if (temp >= 0) {
                mpz_add_ui(rz->z, Pympz_AS_MPZ(a), temp);
            }
            else {
                mpz_sub_ui(rz->z, Pympz_AS_MPZ(a), -temp);
            }
            return (PyObject*)rz;
        }
        if (CHECK_MPZANY(b)) {
            TRACE("Adding (mpz,mpz)\n");
            mpz_add(rz->z, Pympz_AS_MPZ(a), Pympz_AS_MPZ(b));
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (CHECK_MPZANY(b)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(a)) {
            TRACE("Adding (long,mpz)\n");
            temp = PyLong_AsLongAndOverflow(a, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, a);
                mpz_add(rz->z, Pympz_AS_MPZ(b), tempz);
                mpz_cloc(tempz);
            }
            else if (temp >=0) {
                mpz_add_ui(rz->z, Pympz_AS_MPZ(b), temp);
            }
            else {
                mpz_sub_ui(rz->z, Pympz_AS_MPZ(b), -temp);
            }
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

#ifdef WITHMPFR
    if (Pympfr_CheckAndExp(a)) {
        if (!(rf = Pympfr_new(0)))
            return NULL;
        if (Pympfr_CheckAndExp(b)) {
            TRACE("Adding (mpf,mpf)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_add(rf->f, Pympfr_AS_MPFR(a), Pympfr_AS_MPFR(b),
                              context->now.mpfr_round);
            MPFR_CLEANUP_RF("addition");
        }
        if (isInteger(b)) {
            TRACE("Adding (mpf,mpz)\n");
            if (!(pbz = Pympz_From_Integer(b))) {
                SYSTEM_ERROR("Can not convert number to mpz");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_add_z(rf->f, Pympfr_AS_MPFR(a), pbz->z,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)pbz);
            MPFR_CLEANUP_RF("addition");
        }
        if (isRational(b)) {
            TRACE("Adding (mpf,mpq)\n");
            if (!(pbq = Pympq_From_Rational(b))) {
                SYSTEM_ERROR("Can not convert number to mpq");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_add_q(rf->f, Pympfr_AS_MPFR(a), pbq->q,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)pbq);
            MPFR_CLEANUP_RF("addition");
        }
        if (PyFloat_Check(b)) {
            TRACE("Adding (mpf,float)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_add_d(rf->f, Pympfr_AS_MPFR(a), PyFloat_AS_DOUBLE(b),
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)pbq);
            MPFR_CLEANUP_RF("addition");
        }
        Py_DECREF((PyObject*)rf);
    }

    if (Pympfr_CheckAndExp(b)) {
        if (!(rf = Pympfr_new(0)))
            return NULL;
        if (isInteger(a)) {
            TRACE("Adding (mpz,mpf)\n");
            if (!(paz = Pympz_From_Integer(a))) {
                SYSTEM_ERROR("Can not convert number to mpz");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_add_z(rf->f, Pympfr_AS_MPFR(b), paz->z,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)paz);
            MPFR_CLEANUP_RF("addition");
        }
        if (isRational(a)) {
            TRACE("Adding (mpq,mpf)\n");
            if (!(paq = Pympq_From_Rational(a))) {
                SYSTEM_ERROR("Can not convert number to mpq");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_add_q(rf->f, Pympfr_AS_MPFR(b), paq->q,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)paq);
            MPFR_CLEANUP_RF("addition");
        }
        if (PyFloat_Check(a)) {
            TRACE("Adding (float,mpf)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_add_d(rf->f, Pympfr_AS_MPFR(b), PyFloat_AS_DOUBLE(a),
                                context->now.mpfr_round);
            MPFR_CLEANUP_RF("addition");
        }
        Py_DECREF((PyObject*)rf);
    }
#endif

    if (isInteger(a) && isInteger(b)) {
        TRACE("Adding (integer,integer)\n");
        paz = Pympz_From_Integer(a);
        pbz = Pympz_From_Integer(b);
        if (!paz || !pbz) {
            SYSTEM_ERROR("Can not convert integer to mpz");
            Py_XDECREF((PyObject*)paz);
            Py_XDECREF((PyObject*)pbz);
            return NULL;
        }
        if (!(rz = Pympz_new())) {
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        mpz_add(rz->z, paz->z, pbz->z);
        Py_DECREF((PyObject*)paz);
        Py_DECREF((PyObject*)pbz);
        return (PyObject*)rz;
    }

    if (isRational(a) && isRational(b)) {
        TRACE("Adding (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(rq = Pympq_new())) {
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpq_add(rq->q, paq->q, pbq->q);
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        return (PyObject*)rq;
    }

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("Adding (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert number to mpf");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (!(rf = Pympfr_new(0))) {
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        rf->rc = mpfr_add(rf->f, paf->f, pbf->f, context->now.mpfr_round);
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        MPFR_CLEANUP_RF("addition");
    }
#else
    /* Support mpz+float and float+mpz. */
    if (CHECK_MPZANY(a) && PyFloat_Check(b)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(a));
        tempdouble = tempdouble+PyFloat_AsDouble(b);
        return PyFloat_FromDouble(tempdouble);
    }
    if (CHECK_MPZANY(b) && PyFloat_Check(a)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(b));
        tempdouble = PyFloat_AsDouble(a)+tempdouble;
        return PyFloat_FromDouble(tempdouble);
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}

/* Generic Subtraction
 *
 * Follows the same conversion rules as Pympany_add.
 */

static PyObject *
Pympany_sub(PyObject *a, PyObject *b)
{
    mpz_t tempz;
    PympzObject *rz = 0, *paz = 0, *pbz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *rf = 0, *paf = 0, *pbf = 0;
#else
    double tempdouble;
#endif
    long temp;
    int overflow;

    if (CHECK_MPZANY(a)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(b)) {
            TRACE("Subtracting (mpz,long)\n");
            temp = PyLong_AsLongAndOverflow(b, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, b);
                mpz_sub(rz->z, Pympz_AS_MPZ(a), tempz);
                mpz_cloc(tempz);
            }
            else if (temp >= 0) {
                mpz_sub_ui(rz->z, Pympz_AS_MPZ(a), temp);
            }
            else {
                mpz_add_ui(rz->z, Pympz_AS_MPZ(a), -temp);
            }
            return (PyObject*)rz;
        }
        if (Pympz_Check(b)) {
            TRACE("Subtracting (mpz,mpz)\n");
            mpz_sub(rz->z, Pympz_AS_MPZ(a), Pympz_AS_MPZ(b));
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (CHECK_MPZANY(b)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(a)) {
            TRACE("Subtracting (long,mpz)\n");
            temp = PyLong_AsLongAndOverflow(a, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, a);
                mpz_sub(rz->z, tempz, Pympz_AS_MPZ(b));
                mpz_cloc(tempz);
            }
            else if (temp >= 0) {
                mpz_ui_sub(rz->z, temp, Pympz_AS_MPZ(b));
            }
            else {
                mpz_add_ui(rz->z, Pympz_AS_MPZ(b), -temp);
                mpz_neg(rz->z, rz->z);
            }
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

#ifdef WITHMPFR
    if (Pympfr_CheckAndExp(a)) {
        if (!(rf = Pympfr_new(0)))
            return NULL;
        if (Pympfr_CheckAndExp(b)) {
            TRACE("Subtracting (mpf,mpf)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_sub(rf->f, Pympfr_AS_MPFR(a), Pympfr_AS_MPFR(b),
                              context->now.mpfr_round);
            MPFR_CLEANUP_RF("subtraction");
        }
        if (isInteger(b)) {
            TRACE("Subtracting (mpf,mpz)\n");
            if (!(pbz = Pympz_From_Integer(b))) {
                SYSTEM_ERROR("Can not convert number to mpz");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_sub_z(rf->f, Pympfr_AS_MPFR(a), pbz->z,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)pbz);
            MPFR_CLEANUP_RF("subtraction");
        }
        if (isRational(b)) {
            TRACE("Subtracting (mpf,mpq)\n");
            if (!(pbq = Pympq_From_Rational(b))) {
                SYSTEM_ERROR("Can not convert number to mpq");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_sub_q(rf->f, Pympfr_AS_MPFR(a), pbq->q,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)pbq);
            MPFR_CLEANUP_RF("subtraction");
        }
        if (PyFloat_Check(b)) {
            TRACE("Subtracting (mpf,float)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_sub_d(rf->f, Pympfr_AS_MPFR(a), PyFloat_AS_DOUBLE(b),
                                context->now.mpfr_round);
            MPFR_CLEANUP_RF("subtraction");
        }
        Py_DECREF((PyObject*)rf);
    }

    if (Pympfr_CheckAndExp(b)) {
        if (!(rf = Pympfr_new(0)))
            return NULL;
        if (isInteger(a)) {
            TRACE("Subtracting (mpz,mpf)\n");
            if (!(paz = Pympz_From_Integer(a))) {
                SYSTEM_ERROR("Can not convert number to mpz");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_sub_z(rf->f, Pympfr_AS_MPFR(b), paz->z, context->now.mpfr_round);
            mpfr_neg(rf->f, rf->f, context->now.mpfr_round);
            Py_DECREF((PyObject*)paz);
            MPFR_CLEANUP_RF("subtraction");
        }
        if (isRational(a)) {
            TRACE("Subtracting (mpq,mpf)\n");
            if (!(paq = Pympq_From_Rational(a))) {
                SYSTEM_ERROR("Can not convert number to mpq");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_add_q(rf->f, Pympfr_AS_MPFR(b), paq->q, context->now.mpfr_round);
            mpfr_neg(rf->f, rf->f, context->now.mpfr_round);
            Py_DECREF((PyObject*)paq);
            MPFR_CLEANUP_RF("subtraction");
        }
        if (PyFloat_Check(a)) {
            TRACE("Subtracting (float,mpf)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_sub_d(rf->f, Pympfr_AS_MPFR(b), PyFloat_AS_DOUBLE(a), context->now.mpfr_round);
            mpfr_neg(rf->f, rf->f, context->now.mpfr_round);
            MPFR_CLEANUP_RF("subtraction");
        }
        Py_DECREF((PyObject*)rf);
    }
#endif

    if (isInteger(a) && isInteger(b)) {
        TRACE("Subtracting (integer,integer)\n");
        paz = Pympz_From_Integer(a);
        pbz = Pympz_From_Integer(b);
        if (!paz || !pbz) {
            SYSTEM_ERROR("Can not convert integer to mpz");
            Py_XDECREF((PyObject*)paz);
            Py_XDECREF((PyObject*)pbz);
            return NULL;
        }
        if (!(rz = Pympz_new())) {
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        mpz_sub(rz->z, paz->z, pbz->z);
        Py_DECREF((PyObject*)paz);
        Py_DECREF((PyObject*)pbz);
        return (PyObject*)rz;
    }

    if (isRational(a) && isRational(b)) {
        TRACE("Subtracting (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(rq = Pympq_new())) {
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpq_sub(rq->q, paq->q, pbq->q);
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        return (PyObject*)rq;
    }

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("Subtracting (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert number to mpf");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (!(rf = Pympfr_new(0))) {
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        rf->rc = mpfr_sub(rf->f, paf->f, pbf->f, context->now.mpfr_round);
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        MPFR_CLEANUP_RF("subtraction");
    }
#else
    /* Support mpz-float and float-mpz. */
    if (CHECK_MPZANY(a) && PyFloat_Check(b)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(a));
        tempdouble = tempdouble-PyFloat_AsDouble(b);
        return PyFloat_FromDouble(tempdouble);
    }
    if (CHECK_MPZANY(b) && PyFloat_Check(a)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(b));
        tempdouble = PyFloat_AsDouble(a)-tempdouble;
        return PyFloat_FromDouble(tempdouble);
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}

/* Generic Multiplication
 *
 * Follows the same conversion rules as Pympany_add.
 */

static PyObject *
Pympany_mul(PyObject *a, PyObject *b)
{
    mpz_t tempz;
    PympzObject *rz = 0, *paz = 0, *pbz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *rf = 0, *paf = 0, *pbf = 0;
#else
    double tempdouble;
#endif
    long temp;
    int overflow;

    if (CHECK_MPZANY(a)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(b)) {
            TRACE("Multiplying (mpz,long)\n");
            temp = PyLong_AsLongAndOverflow(b, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, b);
                mpz_mul(rz->z, Pympz_AS_MPZ(a), tempz);
                mpz_cloc(tempz);
            }
            else {
                mpz_mul_si(rz->z, Pympz_AS_MPZ(a), temp);
            }
            return (PyObject*)rz;
        }
        if (Pympz_Check(b)) {
            TRACE("Multiplying (mpz,mpz)\n");
            mpz_mul(rz->z, Pympz_AS_MPZ(a), Pympz_AS_MPZ(b));
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (CHECK_MPZANY(b)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(a)) {
            TRACE("Multiplying (long,mpz)\n");
            temp = PyLong_AsLongAndOverflow(a, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, a);
                mpz_mul(rz->z, Pympz_AS_MPZ(b), tempz);
                mpz_cloc(tempz);
            }
            else {
                mpz_mul_si(rz->z, Pympz_AS_MPZ(b), temp);
            }
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

#ifdef WITHMPFR
    if (Pympfr_CheckAndExp(a)) {
        if (!(rf = Pympfr_new(0)))
            return NULL;
        if (Pympfr_CheckAndExp(b)) {
            TRACE("Multiplying (mpf,mpf)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_mul(rf->f, Pympfr_AS_MPFR(a), Pympfr_AS_MPFR(b),
                              context->now.mpfr_round);
            MPFR_CLEANUP_RF("multiplication");
        }
        if (isInteger(b)) {
            TRACE("Multiplying (mpf,mpz)\n");
            if (!(pbz = Pympz_From_Integer(b))) {
                SYSTEM_ERROR("Can not convert number to mpz");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_mul_z(rf->f, Pympfr_AS_MPFR(a), pbz->z,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)pbz);
            MPFR_CLEANUP_RF("multiplication");
        }
        if (isRational(b)) {
            TRACE("Multiplying (mpf,mpq)\n");
            if (!(pbq = Pympq_From_Rational(b))) {
                SYSTEM_ERROR("Can not convert number to mpq");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_mul_q(rf->f, Pympfr_AS_MPFR(a), pbq->q,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)pbq);
            MPFR_CLEANUP_RF("multiplication");
        }
        if (PyFloat_Check(b)) {
            TRACE("Multiplying (mpf,float)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_mul_d(rf->f, Pympfr_AS_MPFR(a), PyFloat_AS_DOUBLE(b),
                                context->now.mpfr_round);
            MPFR_CLEANUP_RF("multiplication");
        }
        Py_DECREF((PyObject*)rf);
    }

    if (Pympfr_CheckAndExp(b)) {
        if (!(rf = Pympfr_new(0)))
            return NULL;
        if (isInteger(a)) {
            TRACE("Multiplying (mpz,mpf)\n");
            if (!(paz = Pympz_From_Integer(a))) {
                SYSTEM_ERROR("Can not convert number to mpz");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_mul_z(rf->f, Pympfr_AS_MPFR(b), paz->z,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)paz);
            MPFR_CLEANUP_RF("multiplication");
        }
        if (isRational(a)) {
            TRACE("Multiplying (mpq,mpf)\n");
            if (!(paq = Pympq_From_Rational(a))) {
                SYSTEM_ERROR("Can not convert number to mpq");
                Py_DECREF((PyObject*)rf);
                return NULL;
            }
            mpfr_clear_flags();
            rf->rc = mpfr_mul_q(rf->f, Pympfr_AS_MPFR(b), paq->q,
                                context->now.mpfr_round);
            Py_DECREF((PyObject*)paq);
            MPFR_CLEANUP_RF("multiplication");
        }
        if (PyFloat_Check(a)) {
            TRACE("Multiplying (float,mpf)\n");
            mpfr_clear_flags();
            rf->rc = mpfr_mul_d(rf->f, Pympfr_AS_MPFR(b), PyFloat_AS_DOUBLE(a),
                                context->now.mpfr_round);
            MPFR_CLEANUP_RF("multiplication");
        }
        Py_DECREF((PyObject*)rf);
    }
#endif

    if (isInteger(a) && isInteger(b)) {
        TRACE("Multiplying (integer,integer)\n");
        paz = Pympz_From_Integer(a);
        pbz = Pympz_From_Integer(b);
        if (!paz || !pbz) {
            SYSTEM_ERROR("Can not convert integer to mpz");
            Py_XDECREF((PyObject*)paz);
            Py_XDECREF((PyObject*)pbz);
            return NULL;
        }
        if (!(rz = Pympz_new())) {
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        mpz_mul(rz->z, paz->z, pbz->z);
        Py_DECREF((PyObject*)paz);
        Py_DECREF((PyObject*)pbz);
        return (PyObject*)rz;
    }

    if (isRational(a) && isRational(b)) {
        TRACE("Multiplying (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(rq = Pympq_new())) {
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpq_mul(rq->q, paq->q, pbq->q);
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        return (PyObject*)rq;
    }

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("Multiplying (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert number to mpf");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (!(rf = Pympfr_new(0))) {
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        rf->rc = mpfr_mul(rf->f, paf->f, pbf->f, context->now.mpfr_round);
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        MPFR_CLEANUP_RF("multiplication");
    }
#else
    /* Support mpz*float and float*mpz. */
    if (CHECK_MPZANY(a) && PyFloat_Check(b)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(a));
        tempdouble = tempdouble*PyFloat_AsDouble(b);
        return PyFloat_FromDouble(tempdouble);
    }
    if (CHECK_MPZANY(b) && PyFloat_Check(a)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(b));
        tempdouble = PyFloat_AsDouble(a)*tempdouble;
        return PyFloat_FromDouble(tempdouble);
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}

/* Pympany_floordiv follows the // semantics from Python 3.x. The result is
 * an mpz when the arguments are mpz or mpq, but the result is an mpfr when
 * the arguments are mpfr.
 */

static PyObject *
Pympany_floordiv(PyObject *a, PyObject *b)
{
    mpz_t tempz;
    PympzObject *rz = 0, *paz = 0, *pbz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *rf = 0, *paf = 0, *pbf = 0;
#endif
    long temp;
    int overflow;

    if (CHECK_MPZANY(a)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(b)) {
            TRACE("Floor divide (mpz,long)\n");
            temp = PyLong_AsLongAndOverflow(b, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, b);
                mpz_fdiv_q(rz->z, Pympz_AS_MPZ(a), tempz);
                mpz_cloc(tempz);
            }
            else if (temp == 0) {
                ZERO_ERROR("mpz division by zero");
                Py_DECREF((PyObject*)rz);
                return NULL;
            }
            else if (temp > 0) {
                mpz_fdiv_q_ui(rz->z, Pympz_AS_MPZ(a), temp);
            }
            else {
                mpz_cdiv_q_ui(rz->z, Pympz_AS_MPZ(a), -temp);
                mpz_neg(rz->z, rz->z);
            }
            return (PyObject*)rz;
        }
        if (CHECK_MPZANY(b)) {
            TRACE("Floor divide (mpz,mpz)\n");
            if (mpz_sgn(Pympz_AS_MPZ(b)) == 0) {
                ZERO_ERROR("mpz division by zero");
                Py_DECREF((PyObject*)rz);
                return NULL;
            }
            mpz_fdiv_q(rz->z, Pympz_AS_MPZ(a), Pympz_AS_MPZ(b));
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (CHECK_MPZANY(b)) {
        if (mpz_sgn(Pympz_AS_MPZ(b)) == 0) {
            ZERO_ERROR("mpz division by zero");
            return NULL;
        }
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(a)) {
            TRACE("Floor divide (integer,mpz)\n");
            mpz_inoc(tempz);
            mpz_set_PyLong(tempz, a);
            mpz_fdiv_q(rz->z, tempz, Pympz_AS_MPZ(b));
            mpz_cloc(tempz);
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (isInteger(a) && isInteger(b)) {
        TRACE("Floor divide (integer,integer)\n");
        paz = Pympz_From_Integer(a);
        pbz = Pympz_From_Integer(b);
        if (!paz || !pbz) {
            SYSTEM_ERROR("Can not convert integer to mpz");
            Py_XDECREF((PyObject*)paz);
            Py_XDECREF((PyObject*)pbz);
            return NULL;
        }
        if (mpz_sgn(pbz->z)==0) {
            ZERO_ERROR("mpz division by zero");
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        if (!(rz = Pympz_new())) {
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        mpz_fdiv_q(rz->z, paz->z, pbz->z);
        Py_DECREF((PyObject*)paz);
        Py_DECREF((PyObject*)pbz);
        return (PyObject*)rz;
    }

    if (isRational(a) && isRational(b)) {
        TRACE("Floor divide (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (mpq_sgn(pbq->q)==0) {
            ZERO_ERROR("mpq division by zero");
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(rq = Pympq_new()) || !(rz = Pympz_new())) {
            Py_XDECREF((PyObject*)rq);
            Py_XDECREF((PyObject*)rz);
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpq_div(rq->q, paq->q, pbq->q);
        mpz_fdiv_q(rz->z, mpq_numref(rq->q), mpq_denref(rq->q));
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        Py_DECREF((PyObject*)rq);
        return (PyObject*)rz;
    }

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("Floor divide (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert number to mpf");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (mpfr_zero_p(pbf->f)) {
            context->now.divzero = 1;
            if (context->now.trap_divzero) {
                GMPY_DIVZERO("'mpfr' division by zero");
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
        }
        if (!(rf = Pympfr_new(0))) {
            Py_XDECREF((PyObject*)rf);
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        rf->rc = mpfr_div(rf->f, paf->f, pbf->f, MPFR_RNDD);
        rf->rc = mpfr_floor(rf->f, rf->f);
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        MPFR_CLEANUP_RF("division");
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}

/* Pympany_truediv follows the / semantics from Python 3.x. The result types
 * are:
 *   mpz  / mpz  -> mpfr
 *   mpq  / mpq  -> mpq
 *   mpfr / mpfr -> mpfr
 *
 * The behavior of mpq now mimics the behavior of fractions.Fraction.
 */

static PyObject *
Pympany_truediv(PyObject *a, PyObject *b)
{
    PympzObject *paz = 0, *pbz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *rf = 0, *paf = 0, *pbf = 0;
#else
    double tempdouble;
#endif
    mpq_t tempq;

#ifdef WITHMPFR
    if (Pympfr_CheckAndExp(a) && Pympfr_CheckAndExp(b)) {
        if (mpfr_zero_p(Pympfr_AS_MPFR(b))) {
            context->now.divzero = 1;
            if (context->now.trap_divzero) {
                GMPY_DIVZERO("'mpfr' division by zero");
                return NULL;
            }
        }
        if (!(rf = Pympfr_new(0))) {
            return NULL;
        }
        mpfr_clear_flags();
        rf->rc = mpfr_div(rf->f, Pympfr_AS_MPFR(a), Pympfr_AS_MPFR(b),
                          context->now.mpfr_round);
        MPFR_CLEANUP_RF("division");
    }
#endif

    if (isInteger(a) && isInteger(b)) {
        TRACE("True divide (integer,integer)\n");
        paz = Pympz_From_Integer(a);
        pbz = Pympz_From_Integer(b);
        if (!paz || !pbz) {
            SYSTEM_ERROR("Can not convert number to mpz");
            Py_XDECREF((PyObject*)paz);
            Py_XDECREF((PyObject*)pbz);
            return NULL;
        }
        if (mpz_sgn(pbz->z) == 0) {
            ZERO_ERROR("mpz division by zero");
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
#ifdef WITHMPFR
        if (!(rf = Pympfr_new(0))) {
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
#endif
        mpq_init(tempq);
        mpq_set_num(tempq, paz->z);
        mpq_set_den(tempq, pbz->z);
        mpq_canonicalize(tempq);
#ifdef WITHMPFR
        mpfr_clear_flags();
        rf->rc = mpfr_set_q(rf->f, tempq, context->now.mpfr_round);
#else
        tempdouble = mpq_get_d(tempq);
#endif
        mpq_clear(tempq);
        Py_DECREF((PyObject*)paz);
        Py_DECREF((PyObject*)pbz);
#ifdef WITHMPFR
        MPFR_CLEANUP_RF("division");
#else
        return PyFloat_FromDouble(tempdouble);
#endif
    }

    if (isRational(a) && isRational(b)) {
        TRACE("True divide (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (mpq_sgn(pbq->q)==0) {
            ZERO_ERROR("mpq division by zero");
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(rq = Pympq_new())) {
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpq_div(rq->q, paq->q, pbq->q);
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        return (PyObject*) rq;
    }

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("True divide (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert float to mpfr");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (mpfr_zero_p(pbf->f)) {
            context->now.divzero = 1;
            if (context->now.trap_divzero) {
                GMPY_DIVZERO("'mpfr' division by zero");
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
        }
        if (!(rf = Pympfr_new(0))) {
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        rf->rc = mpfr_div(rf->f, paf->f, pbf->f, context->now.mpfr_round);
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        MPFR_CLEANUP_RF("division");
    }
#else
    /* Support mpz/float and float/mpz. */
    if (CHECK_MPZANY(a) && PyFloat_Check(b)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(a));
        tempdouble = tempdouble/PyFloat_AsDouble(b);
        return PyFloat_FromDouble(tempdouble);
    }
    if (CHECK_MPZANY(b) && PyFloat_Check(a)) {
        tempdouble = mpz_get_d(Pympz_AS_MPZ(b));
        tempdouble = PyFloat_AsDouble(a)/tempdouble;
        return PyFloat_FromDouble(tempdouble);
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}

#ifdef PY2
/* Pympany_div2 follows the conversions rules for Python 2.x. The behavior is
 * a mix of floordiv and truediv. The type conversion behavior is:
 *   mpz  / mpz  -> mpz
 *   mpq  / mpq  -> mpq
 *   mpfr / mpfr -> mpfr
 *
 * A division operator with these properties is not available with Python 3.x.
 */

static PyObject *
Pympany_div2(PyObject *a, PyObject *b)
{
    mpz_t tempz;
    PympzObject *rz = 0, *paz = 0, *pbz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *rf = 0, *paf = 0, *pbf = 0;
#endif
    long temp;
    int overflow;

    /* Use floordiv for integer types. */

    if (CHECK_MPZANY(a)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(b)) {
            TRACE("Floor divide (mpz,long)\n");
            temp = PyLong_AsLongAndOverflow(b, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, b);
                mpz_fdiv_q(rz->z, Pympz_AS_MPZ(a), tempz);
                mpz_cloc(tempz);
            }
            else if (temp == 0) {
                ZERO_ERROR("mpz division by zero");
                Py_DECREF((PyObject*)rz);
                return NULL;
            }
            else if (temp > 0) {
                mpz_fdiv_q_ui(rz->z, Pympz_AS_MPZ(a), temp);
            }
            else {
                mpz_cdiv_q_ui(rz->z, Pympz_AS_MPZ(a), -temp);
                mpz_neg(rz->z, rz->z);
            }
            return (PyObject*)rz;
        }
        if (CHECK_MPZANY(b)) {
            TRACE("Floor divide (mpz,mpz)\n");
            if (mpz_sgn(Pympz_AS_MPZ(b)) == 0) {
                ZERO_ERROR("mpz division by zero");
                Py_DECREF((PyObject*)rz);
                return NULL;
            }
            mpz_fdiv_q(rz->z, Pympz_AS_MPZ(a), Pympz_AS_MPZ(b));
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (isInteger(a) && isInteger(b)) {
        TRACE("Floor divide (integer,integer)\n");
        paz = Pympz_From_Integer(a);
        pbz = Pympz_From_Integer(b);
        if (!paz || !pbz) {
            SYSTEM_ERROR("Can not convert integer to mpz");
            Py_XDECREF((PyObject*)paz);
            Py_XDECREF((PyObject*)pbz);
            return NULL;
        }
        if (mpz_sgn(pbz->z)==0) {
            ZERO_ERROR("mpz division by zero");
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        if (!(rz = Pympz_new())) {
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        mpz_fdiv_q(rz->z, paz->z, pbz->z);
        Py_DECREF((PyObject*)paz);
        Py_DECREF((PyObject*)pbz);
        return (PyObject*)rz;
    }

    if (isRational(a) && isRational(b)) {
        TRACE("True divide (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (mpq_sgn(pbq->q)==0) {
            ZERO_ERROR("mpq division by zero");
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(rq = Pympq_new())) {
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpq_div(rq->q, paq->q, pbq->q);
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        return (PyObject*) rq;
    }

    /* Use truediv for floating-point types. */

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("True divide (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert number to mpfr");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (mpfr_zero_p(pbf->f)) {
            context->now.divzero = 1;
            if (context->now.trap_divzero) {
                GMPY_DIVZERO("'mpfr' division by zero");
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
        }
        if (!(rf = Pympfr_new(0))) {
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        rf->rc = mpfr_div(rf->f, paf->f, pbf->f, context->now.mpfr_round);
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        MPFR_CLEANUP_RF("division");
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}
#endif

/* Pympany_rem follows the % semantics from Python 3.x. The result types
 * are:
 *   mpz  % mpz  -> mpz
 *   mpq  % mpq  -> mpq
 *   mpfr % mpfr -> mpfr
 *
 * The behavior of mpq now mimics the behavior of fractions.Fraction.
 */

static PyObject *
Pympany_rem(PyObject *a, PyObject *b)
{
    mpz_t tempz;
    PympzObject *rz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *qf = 0, *rf = 0, *paf = 0, *pbf = 0;
#endif
    long temp;
    int overflow;

    if (CHECK_MPZANY(a)) {
        if (!(rz = Pympz_new()))
            return NULL;
        if (PyIntOrLong_Check(b)) {
            TRACE("Modulo (mpz,integer)\n");
            temp = PyLong_AsLongAndOverflow(b, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, b);
                mpz_fdiv_r(rz->z, Pympz_AS_MPZ(a), tempz);
                mpz_cloc(tempz);
            }
            else if (temp > 0) {
                mpz_fdiv_r_ui(rz->z, Pympz_AS_MPZ(a), temp);
            }
            else if (temp == 0) {
                ZERO_ERROR("mpz modulo by zero");
                Py_DECREF((PyObject*)rz);
                return NULL;
            }
            else {
                mpz_cdiv_r_ui(rz->z, Pympz_AS_MPZ(a), -temp);
            }
            return (PyObject*)rz;
        }
        if (CHECK_MPZANY(b)) {
            TRACE("Modulo (integer,integer)\n");
            if (mpz_sgn(Pympz_AS_MPZ(b)) == 0) {
                ZERO_ERROR("mpz modulo by zero");
                Py_DECREF((PyObject*)rz);
                return NULL;
            }
            mpz_fdiv_r(rz->z, Pympz_AS_MPZ(a), Pympz_AS_MPZ(b));
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (CHECK_MPZANY(b)) {
        if (mpz_sgn(Pympz_AS_MPZ(b)) == 0) {
            ZERO_ERROR("mpz division by zero");
            return NULL;
        }
        if (!(rz = Pympz_new())) return NULL;
        if (PyIntOrLong_Check(a)) {
            TRACE("Modulo (integer,mpz)\n");
            mpz_inoc(tempz);
            mpz_set_PyLong(tempz, a);
            mpz_fdiv_r(rz->z, tempz, Pympz_AS_MPZ(b));
            mpz_cloc(tempz);
            return (PyObject*)rz;
        }
        Py_DECREF((PyObject*)rz);
    }

    if (isRational(a) && isRational(b)) {
        TRACE("Modulo (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (mpq_sgn(pbq->q)==0) {
            ZERO_ERROR("mpq modulo by zero");
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(rq = Pympq_new())) {
            Py_XDECREF((PyObject*)rq);
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpz_inoc(tempz);
        mpq_div(rq->q, paq->q, pbq->q);
        mpz_fdiv_q(tempz, mpq_numref(rq->q), mpq_denref(rq->q));
        /* Need to calculate paq - rz * pbq */
        mpq_set_z(rq->q, tempz);
        mpq_mul(rq->q, rq->q, pbq->q);
        mpq_sub(rq->q, paq->q, rq->q);
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        mpz_cloc(tempz);
        return (PyObject*)rq;
    }

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("Modulo (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert number to mpfr");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (mpfr_zero_p(pbf->f)) {
            context->now.divzero = 1;
            if (context->now.trap_divzero) {
                GMPY_DIVZERO("'mpfr' division by zero");
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
        }
        if (!(rf = Pympfr_new(0)) || !(qf = Pympfr_new(0))) {
            Py_XDECREF((PyObject*)rf);
            Py_XDECREF((PyObject*)qf);
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        if (mpfr_nan_p(paf->f) || mpfr_nan_p(pbf->f) || mpfr_inf_p(paf->f)) {
            context->now.invalid = 1;
            if (context->now.trap_invalid) {
                GMPY_INVALID("invalid operation in 'mpfr' rem");
                Py_DECREF((PyObject*)rf);
                Py_DECREF((PyObject*)qf);
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
            else {
                mpfr_set_nan(rf->f);
            }
        }
        else if (mpfr_inf_p(pbf->f)) {
            context->now.invalid = 1;
            if (context->now.trap_invalid) {
                GMPY_INVALID("invalid operation in 'mpfr' rem");
                Py_DECREF((PyObject*)rf);
                Py_DECREF((PyObject*)qf);
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
            if (mpfr_signbit(pbf->f)) {
                mpfr_set_inf(rf->f, -1);
            }
            else {
                rf->rc = mpfr_set(rf->f, paf->f, context->now.mpfr_round);
            }
        }
        else {
            mpfr_div(qf->f, paf->f, pbf->f, MPFR_RNDD);
            mpfr_floor(qf->f, qf->f);
            rf->rc = mpfr_fms(rf->f, qf->f, pbf->f, paf->f, context->now.mpfr_round);
            mpfr_neg(rf->f, rf->f, context->now.mpfr_round);
        }
        Py_XDECREF((PyObject*)qf);
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        MPFR_CLEANUP_RF("rem");
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}

/* Pympany_divmod follows the semantics from Python 3.x. The result types
 * are:
 *   divmod(mpz, mpz)   -> (mpz, mpz)
 *   divmod(mpq, mpq)   -> (mpz, mpq)
 *   divmod(mpfr, mpfr) -> (mpfr, mpfr)
 *
 * The behavior of mpq now mimics the behavior of fractions.Fraction.
 */

static PyObject *
Pympany_divmod(PyObject *a, PyObject *b)
{
    PyObject *r = 0;
    mpz_t tempz;
    PympzObject *qz = 0, *rz = 0, *paz = 0, *pbz = 0;
    PympqObject *rq = 0, *paq = 0, *pbq = 0;
#ifdef WITHMPFR
    PympfrObject *qf = 0, *rf = 0, *paf = 0, *pbf = 0;
#endif
    long temp;
    int overflow;

    if (CHECK_MPZANY(a)) {
        if (!(r=PyTuple_New(2)) || !(rz=Pympz_new()) || !(qz=Pympz_new())) {
            Py_XDECREF((PyObject*)rz);
            Py_XDECREF((PyObject*)qz);
            Py_XDECREF(r);
            return NULL;
        }
        if (PyIntOrLong_Check(b)) {
            TRACE("divmod (mpz,integer)\n");
            temp = PyLong_AsLongAndOverflow(b, &overflow);
            if (overflow) {
                mpz_inoc(tempz);
                mpz_set_PyLong(tempz, b);
                mpz_fdiv_qr(qz->z, rz->z, Pympz_AS_MPZ(a), tempz);
                mpz_cloc(tempz);
            }
            else if (temp > 0) {
                mpz_fdiv_qr_ui(qz->z, rz->z, Pympz_AS_MPZ(a), temp);
            }
            else if (temp == 0) {
                ZERO_ERROR("mpz divmod by zero");
                Py_DECREF((PyObject*)rz);
                Py_DECREF((PyObject*)qz);
                Py_DECREF(r);
                return NULL;
            }
            else {
                mpz_cdiv_qr_ui(qz->z, rz->z, Pympz_AS_MPZ(a), -temp);
                mpz_neg(qz->z, qz->z);
            }
            PyTuple_SET_ITEM(r, 0, (PyObject*)qz);
            PyTuple_SET_ITEM(r, 1, (PyObject*)rz);
            return r;
        }
        if (CHECK_MPZANY(b)) {
            TRACE("divmod (mpz,mpz)\n");
            if (mpz_sgn(Pympz_AS_MPZ(b)) == 0) {
                ZERO_ERROR("mpz divmod by zero");
                Py_DECREF((PyObject*)rz);
                Py_DECREF((PyObject*)qz);
                Py_DECREF(r);
                return NULL;
            }
            mpz_fdiv_qr(qz->z, rz->z, Pympz_AS_MPZ(a), Pympz_AS_MPZ(b));
            PyTuple_SET_ITEM(r, 0, (PyObject*)qz);
            PyTuple_SET_ITEM(r, 1, (PyObject*)rz);
            return r;
        }
        Py_DECREF((PyObject*)rz);
        Py_DECREF((PyObject*)qz);
        Py_DECREF(r);
    }

    if (CHECK_MPZANY(b)) {
        if (mpz_sgn(Pympz_AS_MPZ(b)) == 0) {
            ZERO_ERROR("mpz modulo by zero");
            return NULL;
        }
        if (!(r=PyTuple_New(2)) || !(rz=Pympz_new()) || !(qz=Pympz_new())) {
            Py_XDECREF((PyObject*)rz);
            Py_XDECREF((PyObject*)qz);
            Py_XDECREF(r);
            return NULL;
        }
        if (PyIntOrLong_Check(a)) {
            TRACE("divmod (integer,mpz)\n");
            mpz_inoc(tempz);
            mpz_set_PyLong(tempz, a);
            mpz_fdiv_qr(qz->z, rz->z, tempz, Pympz_AS_MPZ(b));
            mpz_cloc(tempz);
            PyTuple_SET_ITEM(r, 0, (PyObject*)qz);
            PyTuple_SET_ITEM(r, 1, (PyObject*)rz);
            return r;
        }
        Py_DECREF((PyObject*)rz);
        Py_DECREF((PyObject*)qz);
        Py_DECREF(r);
    }

    if (isInteger(a) && isInteger(b)) {
        TRACE("Divmod (integer,integer)\n");
        paz = Pympz_From_Integer(a);
        pbz = Pympz_From_Integer(b);
        if (!paz || !pbz) {
            SYSTEM_ERROR("Can not convert integer to mpz");
            Py_XDECREF((PyObject*)paz);
            Py_XDECREF((PyObject*)pbz);
            return NULL;
        }
        if (mpz_sgn(pbz->z) == 0) {
            ZERO_ERROR("mpz divmod by zero");
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        if (!(r = PyTuple_New(2)) || !(rz = Pympz_new()) || !(qz = Pympz_new())) {
            Py_XDECREF((PyObject*)r);
            Py_XDECREF((PyObject*)rz);
            Py_XDECREF((PyObject*)qz);
            Py_DECREF((PyObject*)paz);
            Py_DECREF((PyObject*)pbz);
            return NULL;
        }
        mpz_fdiv_qr(qz->z, rz->z, paz->z, pbz->z);
        Py_DECREF((PyObject*)paz);
        Py_DECREF((PyObject*)pbz);
        PyTuple_SET_ITEM(r, 0, (PyObject*)qz);
        PyTuple_SET_ITEM(r, 1, (PyObject*)rq);
        return r;
    }

    if (isRational(a) && isRational(b)) {
        TRACE("Divmod (rational,rational)\n");
        paq = Pympq_From_Rational(a);
        pbq = Pympq_From_Rational(b);
        if (!paq || !pbq) {
            SYSTEM_ERROR("Can not convert rational to mpq");
            Py_XDECREF((PyObject*)paq);
            Py_XDECREF((PyObject*)pbq);
            return NULL;
        }
        if (mpq_sgn(pbq->q)==0) {
            ZERO_ERROR("mpq divmod by zero");
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        if (!(r = PyTuple_New(2)) || !(rq = Pympq_new()) || !(qz = Pympz_new())) {
            Py_XDECREF((PyObject*)r);
            Py_XDECREF((PyObject*)rq);
            Py_XDECREF((PyObject*)qz);
            Py_DECREF((PyObject*)paq);
            Py_DECREF((PyObject*)pbq);
            return NULL;
        }
        mpq_div(rq->q, paq->q, pbq->q);
        mpz_fdiv_q(qz->z, mpq_numref(rq->q), mpq_denref(rq->q));
        /* Need to calculate paq - rz * pbq */
        mpq_set_z(rq->q, qz->z);
        mpq_mul(rq->q, rq->q, pbq->q);
        mpq_sub(rq->q, paq->q, rq->q);
        Py_DECREF((PyObject*)paq);
        Py_DECREF((PyObject*)pbq);
        PyTuple_SET_ITEM(r, 0, (PyObject*)qz);
        PyTuple_SET_ITEM(r, 1, (PyObject*)rq);
        return r;
    }

#ifdef WITHMPFR
    if (isReal(a) && isReal(b)) {
        TRACE("Divmod (number,number)\n");
        paf = Pympfr_From_Real(a, 0);
        pbf = Pympfr_From_Real(b, 0);
        if (!paf || !pbf) {
            SYSTEM_ERROR("Can not convert number to mpfr");
            Py_XDECREF((PyObject*)paf);
            Py_XDECREF((PyObject*)pbf);
            return NULL;
        }
        if (mpfr_zero_p(pbf->f)) {
            context->now.divzero = 1;
            if (context->now.trap_divzero) {
                GMPY_DIVZERO("'mpfr' divmod by zero");
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
        }
        if (!(r = PyTuple_New(2)) || !(qf = Pympfr_new(0)) || !(rf = Pympfr_new(0))) {
            Py_XDECREF(r);
            Py_XDECREF((PyObject*)qf);
            Py_XDECREF((PyObject*)rf);
            Py_DECREF((PyObject*)paf);
            Py_DECREF((PyObject*)pbf);
            return NULL;
        }
        mpfr_clear_flags();
        if (mpfr_nan_p(paf->f) || mpfr_nan_p(pbf->f) || mpfr_inf_p(paf->f)) {
            context->now.invalid = 1;
            if (context->now.trap_invalid) {
                GMPY_INVALID("invalid operation in 'mpfr' divmod");
                Py_DECREF(r);
                Py_DECREF((PyObject*)qf);
                Py_DECREF((PyObject*)rf);
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
            else {
                mpfr_set_nan(qf->f);
                mpfr_set_nan(rf->f);
            }
        }
        else if (mpfr_inf_p(pbf->f)) {
            context->now.invalid = 1;
            if (context->now.trap_invalid) {
                GMPY_INVALID("invalid operation in 'mpfr' divmod");
                Py_DECREF(r);
                Py_DECREF((PyObject*)qf);
                Py_DECREF((PyObject*)rf);
                Py_DECREF((PyObject*)paf);
                Py_DECREF((PyObject*)pbf);
                return NULL;
            }
            else {
                if (mpfr_zero_p(paf->f)) {
                    mpfr_set_zero(qf->f, mpfr_sgn(pbf->f));
                    mpfr_set_zero(rf->f, mpfr_sgn(pbf->f));
                }
                else if ((mpfr_signbit(paf->f)) != (mpfr_signbit(pbf->f))) {
                    mpfr_set_si(qf->f, -1, context->now.mpfr_round);
                    mpfr_set_inf(rf->f, mpfr_sgn(pbf->f));
                }
                else {
                    mpfr_set_si(qf->f, 0, context->now.mpfr_round);
                    rf->rc = mpfr_set(rf->f, paf->f, context->now.mpfr_round);
                }
            }
        }
        else {
            mpfr_div(qf->f, paf->f, pbf->f, MPFR_RNDD);
            mpfr_floor(qf->f, qf->f);
            rf->rc = mpfr_fms(rf->f, qf->f, pbf->f, paf->f, context->now.mpfr_round);
            mpfr_neg(rf->f, rf->f, context->now.mpfr_round);
        }
        Py_DECREF((PyObject*)paf);
        Py_DECREF((PyObject*)pbf);
        SUBNORMALIZE(rf);
        SUBNORMALIZE(qf);
        MERGE_FLAGS;
        if (mpfr_underflow_p() && context->now.trap_underflow) {
            GMPY_UNDERFLOW("underflow in 'mpfr' divmod");
            Py_DECREF((PyObject*)rf);
            Py_DECREF((PyObject*)qf);
            Py_DECREF(r);
            return NULL;
        }
        if (mpfr_overflow_p() && context->now.trap_overflow) {
            GMPY_OVERFLOW("overflow in 'mpfr' divmod");
            Py_DECREF((PyObject*)rf);
            Py_DECREF((PyObject*)qf);
            Py_DECREF(r);
            return NULL;
        }
        if (mpfr_inexflag_p() && context->now.trap_inexact) {
            GMPY_INEXACT("inexact result in 'mpfr' divmod");
            Py_DECREF((PyObject*)rf);
            Py_DECREF((PyObject*)qf);
            Py_DECREF(r);
            return NULL;
        }
        PyTuple_SET_ITEM(r, 0, (PyObject*)qf);
        PyTuple_SET_ITEM(r, 1, (PyObject*)rf);
        return r;
    }
#endif

    Py_RETURN_NOTIMPLEMENTED;
}
