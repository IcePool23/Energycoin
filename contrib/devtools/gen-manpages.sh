#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

NRGCD=${NRGCD:-$SRCDIR/nrgcd}
NRGCCLI=${NRGCCLI:-$SRCDIR/nrgc-cli}
NRGCTX=${NRGCTX:-$SRCDIR/nrgc-tx}
NRGCQT=${NRGCQT:-$SRCDIR/qt/nrgc-qt}

[ ! -x $NRGCD ] && echo "$NRGCD not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
NRGCVER=($($NRGCCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for nrgcd if --version-string is not set,
# but has different outcomes for nrgc-qt and nrgc-cli.
echo "[COPYRIGHT]" > footer.h2m
$NRGCD --version | sed -n '1!p' >> footer.h2m

for cmd in $NRGCD $NRGCCLI $NRGCTX $NRGCQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${NRGCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${NRGCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
