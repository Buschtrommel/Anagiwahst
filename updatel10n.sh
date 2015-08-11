#!/bin/bash

for LANG in en_GB en_US
do
lupdate-qt5 -source-language en -locations relative -no-obsolete -pluralonly . -ts l10n/anagiwahst_$LANG.ts
done

lupdate-qt5 -source-language en -locations relative -no-obsolete . -ts l10n/anagiwahst.ts
