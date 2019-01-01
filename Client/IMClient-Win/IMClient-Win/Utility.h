#pragma once
#include "stdafx.h"
#include "Base64.h"
#include "openssl/err.h"
#include "openssl/pem.h"
#include "openssl/rsa.h"
#include "openssl/crypto.h"
#include "tinyxml2/tinyxml2.h"
#include "NetWorker.h"
#pragma comment(lib, "openssl/libcrypto32MD.lib")
#pragma comment(lib, "openssl/libssl32MD.lib")
#pragma comment(lib, "tinyxml2/tinyxml2.lib")


class CUtility
{
public:
	CUtility() {};
	~CUtility() {};

	// ANSI<->UTF16<->UTF8
	static char* Utf16ToUtf8(const WCHAR* wideString) {
		DWORD size = WideCharToMultiByte(CP_UTF8, 0, wideString, wcslen(wideString), nullptr, 0, nullptr, nullptr);
		char* output = new char[size + 1];
		memset(output, 0, size + 1);
		WideCharToMultiByte(CP_UTF8, 0, wideString, wcslen(wideString), output, size, nullptr, nullptr);
		output[size] = '\0';
		return output;
	};
	static WCHAR* Utf8ToUtf16(const char* string) {
		DWORD size = MultiByteToWideChar(CP_UTF8, 0, string, strlen(string), nullptr, 0);
		wchar_t* output = new wchar_t[size + 1];
		memset(output, 0, (size + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_UTF8, 0, string, strlen(string), output, size);
		output[size] = '\0';
		return output;
	};
	static char* Utf16ToGB(const WCHAR* wideString) {
		DWORD size = WideCharToMultiByte(936, 0, wideString, wcslen(wideString), nullptr, 0, nullptr, nullptr);
		char* output = new char[size + 1];
		memset(output, 0, size + 1);
		WideCharToMultiByte(936, 0, wideString, wcslen(wideString), output, size, nullptr, nullptr);
		output[size] = '\0';
		return output;
	};
	static WCHAR* GBToUtf16(const char* string) {
		DWORD size = MultiByteToWideChar(936, 0, string, strlen(string), nullptr, 0);
		wchar_t* output = new wchar_t[size + 1];
		memset(output, 0, (size + 1) * sizeof(wchar_t));
		MultiByteToWideChar(936, 0, string, strlen(string), output, size);
		output[size] = '\0';
		return output;
	}

	// RSA
	static string RSAEncrypt(string data) {
		const char* pubkey = "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC2v3F2OIZWpbI05cc4pwGY/jnw\nlCZMdo5zMKSq1MxNoTh3hXhm5txkRt4ZQFqdS485zxissUz4ukAebOguolXUrtXE\nI1lxJEDd4CmidTdiK1zxE6vEN955uZQkSF7hBJ6EvoLzNom/Vcnn66zqS506e7wH\nKIDKDJb4K8yHbSqHKQIDAQAB\n-----END PUBLIC KEY-----\n";

		string strRet = "";
		BIO* bio = BIO_new(BIO_s_mem());
		BIO_puts(bio, pubkey);
		RSA* rsa = nullptr;
		EVP_PKEY* evp_key = nullptr;
		evp_key = PEM_read_bio_PUBKEY(bio, &evp_key, NULL, NULL);
		rsa = EVP_PKEY_get1_RSA(evp_key);
		if (!rsa) {
			return "";
		}

		int nLen = RSA_size(rsa);
		char* pEncode = new char[nLen + 1];
		int ret = RSA_public_encrypt(data.length(), reinterpret_cast<const unsigned char*>(data.c_str()),
			reinterpret_cast<unsigned char*>(pEncode), rsa, RSA_PKCS1_PADDING);
		if (ret >= 0){
			strRet = base64_encode((UCHAR*)pEncode, nLen);
			//cout << "\n\n" << strRet  << endl << endl << endl;
		}
		delete[] pEncode;
		RSA_free(rsa);
		BIO_free(bio);

		CRYPTO_cleanup_all_ex_data();
		return strRet;
	}
	static wstring RSAEncrypt(wstring data) {
		char* pData = CUtility::Utf16ToGB(data.data());
		string strEncrypt = CUtility::RSAEncrypt(pData);
		delete[] pData;
		WCHAR* pWData = CUtility::GBToUtf16(strEncrypt.data());
		wstring wStrEncrypt = wstring(pWData);
		delete[] pWData;
		return wStrEncrypt;
	}

	static wstring GetHeadImgName(int sex, int online) {
		wstring fileName = L"";
		switch (sex) {
		case 0:	// male
			switch(online) {
			case 0:
				fileName = L"HeadMaleOffline.png";
				break;
			case 1:
				fileName = L"HeadMale.png";
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
			break;
		case 1:	// femal
			switch (online) {
			case 0:
				fileName = L"HeadFemaleOffline.png";
				break;
			case 1:
				fileName = L"HeadFemale.png";
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
			break;
		case 2:	// others
			switch (online) {
			case 0:
				fileName = L"AnonymousOffline.png";
				break;
			case 1:
				fileName = L"Anonymous.png";
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		return fileName;
	}

	// xml user info R/W
	static LONG WriteXmlUsrInfo(wstring xmlPath, ST_ACCOUNT_INFO& usrInfo)
	{
		LONG ret = 0;
		char* pCode = Utf16ToGB(usrInfo.ID);
		char* pPwd = Utf16ToGB(usrInfo.pwd);
		char* pXmlPath = Utf16ToGB(xmlPath.data());
		tinyxml2::XMLDocument doc;
		ret = doc.LoadFile(pXmlPath);

		if (0 == ret) {
			if (doc.RootElement()) {
				tinyxml2::XMLElement* userEle = doc.RootElement()->FirstChildElement();
				bool bFound = false;
				while (userEle) {
					tinyxml2::XMLElement* infoCode = userEle->FirstChildElement("Code");
					tinyxml2::XMLElement* infoPwd = userEle->FirstChildElement("Password");
					char* pCode = Utf16ToGB(usrInfo.ID);
					char* pPwd = Utf16ToGB(usrInfo.pwd);
					if (0 == strcmp(pCode, infoCode->GetText())) {
						// Update
						bFound = true;
						// TODO: Encrypting password
						infoPwd->SetText(pPwd);
						ret = doc.SaveFile(pXmlPath);
					}
					userEle = userEle->NextSiblingElement();
				}
				if (!bFound) {
					// Append
					tinyxml2::XMLElement* xmlUser = doc.NewElement("User");
					doc.RootElement()->InsertEndChild(xmlUser);
					tinyxml2::XMLElement* xmlCode = doc.NewElement("Code");
					xmlCode->SetText(pCode);
					xmlUser->InsertEndChild(xmlCode);
					tinyxml2::XMLElement* xmlPwd = doc.NewElement("Password");
					// TODO: Encrypting password
					xmlPwd->SetText(pPwd);
					xmlUser->InsertEndChild(xmlPwd);
					ret = doc.SaveFile(pXmlPath);
				}
			}
			else {
				ret = -1;
			}
		}
		else {
			// Create
			FILE* fp = nullptr;
			fopen_s(&fp, pXmlPath, "w+");
			fclose(fp);

			const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
			tinyxml2::XMLDocument doc;
			doc.Parse(declaration);
			tinyxml2::XMLElement* root = doc.NewElement("UserInfo");
			doc.InsertEndChild(root);

			tinyxml2::XMLElement* xmlUser = doc.NewElement("User");
			root->InsertEndChild(xmlUser);

			tinyxml2::XMLElement* xmlCode = doc.NewElement("Code");
			xmlCode->SetText(pCode);
			xmlUser->InsertEndChild(xmlCode);

			tinyxml2::XMLElement* xmlPwd = doc.NewElement("Password");
			// TODO: Encrypting password
			xmlPwd->SetText(pPwd);
			xmlUser->InsertEndChild(xmlPwd);

			ret = doc.SaveFile(pXmlPath);
		}

		delete[] pXmlPath;
		delete[] pCode;
		delete[] pPwd;
		return ret;
	}

	static LONG GetXmlUsrInfo(wstring xmlPath, vector<ST_ACCOUNT_INFO>& usrInfo)
	{
		LONG ret = 0;
		char* pXmlPath = Utf16ToGB(xmlPath.data());
		tinyxml2::XMLDocument doc;
		ret = doc.LoadFile(pXmlPath);
		
		if (0 == ret) {
			if (doc.RootElement()) {
				tinyxml2::XMLElement* userEle = doc.RootElement()->FirstChildElement();
				while (userEle) {
					tinyxml2::XMLElement* infoCode = userEle->FirstChildElement("Code");
					tinyxml2::XMLElement* infoPwd = userEle->FirstChildElement("Password");
					WCHAR* pWcode = GBToUtf16(infoCode->GetText());
					WCHAR* pWpwd = GBToUtf16(infoPwd->GetText());
					userEle = userEle->NextSiblingElement();
					ST_ACCOUNT_INFO info = { 0 };
					memcpy_s(info.ID, sizeof(info.ID), pWcode, wcslen(pWcode) * sizeof(WCHAR));
					memcpy_s(info.pwd, sizeof(info.pwd), pWpwd, wcslen(pWpwd) * sizeof(WCHAR));
					usrInfo.push_back(info);
					delete[] pWcode;
					delete[] pWpwd;
				}
			}
			else {
				ret = -1;
			}
		}
		else {
			ret = -1;
		}

		delete[] pXmlPath;
		return ret;
	}
};
