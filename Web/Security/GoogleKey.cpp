//===============
// GoogleKey.cpp
//===============

#include "pch.h"


//=======
// Using
//=======

#include "Json/JsonElement.h"
#include "Network/Https/HttpsClient.h"
#include "Network/Tls/TlsCertificate.h"
#include "Security/Rsa/RsaKey.h"
#include "Storage/Encoding/Base64.h"
#include "Storage/Buffer.h"
#include "Resources/Certificates/Google.h"
#include "GoogleKey.h"

using namespace Json;
using namespace Network::Http;
using namespace Network::Https;
using namespace Network::Tls;
using namespace Resources::Certificates;
using namespace Storage::Encoding;


//===========
// Namespace
//===========

namespace Web {
	namespace Security {


//========
// Common
//========

Handle<GoogleKey> GoogleKey::Get(Handle<String> id)
{
if(!id)
	throw InvalidArgumentException();
TlsCertificate::Add(CERT_GOOGLE_API);
auto con=HttpsClient::Connect("googleapis.com");
auto request=HttpRequest::Create();
request->Method=HttpMethod::Get;
request->Path="/oauth2/v3/certs";
request->Properties->Add("Host", "www.googleapis.com");
con->Send(request);
auto response=con->GetResponse();
if(response->Status!=HttpStatus::Ok)
	throw InvalidArgumentException();
auto json=JsonElement::FromStream(con);
auto keys=json->GetList("keys");
if(!keys)
	throw InvalidArgumentException();
Handle<GoogleKey> key;
for(auto it=keys->First(); it->HasCurrent(); it->MoveNext())
	{
	auto key_json=it->GetCurrent().As<JsonElement>();
	if(!key_json)
		continue;
	auto kid=key_json->GetString("kid");
	auto e=key_json->GetString("e");
	auto n=key_json->GetString("n");
	if(!kid||!e||!n)
		continue;
	auto exp=Base64::Decode(e->Begin(), 0);
	auto mod=Base64::Decode(n->Begin(), 0);
	key=GoogleKey::Create(kid, exp, mod);
	break;
	}
if(!key)
	throw InvalidArgumentException();
return key;
}


//==========================
// Con-/Destructors Private
//==========================

GoogleKey::GoogleKey(Handle<String> id, Handle<Buffer> exp, Handle<Buffer> mod):
RsaKey(exp, mod),
Id(id)
{}

}}