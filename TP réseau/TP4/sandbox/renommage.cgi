#!/bin/bash
#renommage
echo "Content-type: text/html"
echo ""

filesInDir=$(ls)

for file in $filesInDir
do
    if grep -Fxq "#renommage" $file
    then
        continue
    fi
    if grep -Fxq "#monformulaire" $file
    then
        mv $file "formulaire.html"
    fi
    if grep -Fxq "#monscriptcgi" $file
    then
        mv $file "traitement.cgi"
    fi
done



exit 0