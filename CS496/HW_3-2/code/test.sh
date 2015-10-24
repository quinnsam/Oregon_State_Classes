#!/usr/bin/zsh
# Test adding a new public key
echo "Testing Public Key"
echo "* Adding key:"
printf "*-* Adding Normal key:"
curl --silent --data "full-name=Tester one&email=testone@testone.com&comment=testonecomment&expiration=False&pubkey=testonepubkeyone" -H "Accept: application/json" http://localhost:8080/pubkey > /dev/null
if [ $? -ne 0 ]; then
    echo "FAILED[$?]"
else
    echo "PASSED"
fi
printf "*-* Adding Blank 'fullname':"
curl --silent --data "email=testone@testone.com&comment=testonecomment&expiration=False&pubkey=testonepubkeyone" -H "Accept: application/json" http://localhost:8080/pubkey > /dev/null
if [ $? -ne 0 ]; then
    echo "PASSED"
else
    echo "FAILED[$?]"
fi
printf "*-* Adding Blank 'email':"
curl --silent --data "full-name=Tester one&comment=testonecomment&expiration=False&pubkey=testonepubkeyone" -H "Accept: application/json" http://localhost:8080/pubkey > /dev/null
if [ $? -ne 0 ]; then
    echo "PASSED"
else
    echo "FAILED[$?]"
fi
    
echo "Testing People"
printf "* Adding person:     "
curl --silent --data "full-name=Tester One&email=testone@testone.com&phone=1234567890&address=Tester one deress 998765&contacts[]=Tester Two&contacts[]=Tester Three" -H "Accept: application/json" http://localhost:8080/people > /dev/null
if [ $? -ne 0 ]; then
    echo "FAILED[$?]"
    echo "Adding a new Person failed."
else
    echo "PASSED"
fi

#curl --data "full-name=wehetethetnhe&email=quinnsam&phone=77777777777777&address=Myadderess&contacts[]=kelly&contacts[]=Alex&id=4925812092436480" -H "Accept: application/json" http://localhost:8080/people
#curl --data "full-name=wehetethetnhe&email=quinnsam&phone=77777777777777&address=Myadderess&contacts[]=kelly&contacts[]=Alex" -H "Accept: application/json" http://localhost:8080/people

#curl --data "full-name=sam&email=whatwhatwhat&comment=hey&expiration=False&pubkey=keykeykey" -H "Accept: application/json" http://localhost:8080/pubkey

d1=$(curl --silent --data "full-name=thecodegod&email=whatwhatwhat&comment=hey&expiration=False&pubkey=keykeykey&id=5136918324969472" -H "Accept: application/json" http://localhost:8080/pubkey)

echo "$d1" | grep -Po '"key":.*?[^\\], ' | grep -Po '\d+'

