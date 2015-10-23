#!/usr/bin/zsh

#curl --data "full-name=sam&email=quinnsam&comment=hey&expiration=False&pubkey=keykeykey" -H "Accept: application/json" http://localhost:8080/pubkey
curl --data "full-name=sam&email=quinnsam&phone=5417283802&address=Myadderess&contacts=kelly" -H "Accept: application/json" http://localhost:8080/people

