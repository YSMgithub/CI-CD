#!/bin/bash

TELEGRAM_BOT_TOKEN="5354920798:AAFcdLWBLV9gyfC2pkbdIJ1uj-S-pdQT6Ac"
TELEGRAM_USER_ID="988591441"
TIME=10
URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"

if grep -q success status; then
    STATUS="Success"
else
    STATUS="Faild"
fi

TEXT="$1 Status: $STATUS %0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s --max-time $TIME -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null