#include <iostream>

#include <nlohmann/json-schema.hpp>

#include <json-schema-include.hpp>

using nlohmann::json;
using nlohmann::json_schema::json_validator;

// The schema is defined based upon a string literal
static json uri_schema = R"(
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "properties": {
    "myUri": {
      "type":"string",
      "format": "uri"
    }
  }
})"_json;

// The people are defined with brace initialization
static json good_uri = {{"myUri", "http://hostname.com/"}};
static json bad_uri = {{"myUri", "http:/hostname.com/"}};

static void uri_format_checker(const std::string &format, const std::string &value)
{
	if (format == "uri") {
		if (value.find("://") == std::string::npos)
			JSONSV_THROW(std::invalid_argument("URI does not contain :// - invalid"));
	} else
		JSONSV_THROW(std::logic_error("Don't know how to validate " + format));
}

int main()
{
	json_validator validator(nullptr, uri_format_checker); // create validator

	JSONSV_TRY {
		validator.set_root_schema(uri_schema); // insert root-schema
	} JSONSV_CATCH(const std::exception &e) {
	#if defined(JSONSV_EXCEPTIONS)
		std::cerr << "Validation of schema failed, here is why: " << e.what() << "\n";
	#endif
		return EXIT_FAILURE;
	}

	validator.validate(good_uri);

	JSONSV_TRY {
		validator.validate(bad_uri);
	} JSONSV_CATCH(const std::exception &e) {
	#if defined(JSONSV_EXCEPTIONS)
		std::cerr << "Validation expectedly failed, here is why: " << e.what() << "\n";
	#endif
	}

	return EXIT_SUCCESS;
}
