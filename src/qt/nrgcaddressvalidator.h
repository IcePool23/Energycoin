// Copyright (c) 2011-2014 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2023-2024 The Nrgc Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef NRGC_QT_NRGCADDRESSVALIDATOR_H
#define NRGC_QT_NRGCADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class NrgcAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit NrgcAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Nrgc address widget validator, checks for a valid raven address.
 */
class NrgcAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit NrgcAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // NRGC_QT_NRGCADDRESSVALIDATOR_H
