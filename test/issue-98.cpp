#include <nlohmann/json-schema.hpp>

#include <json-schema-include.hpp>

int main(void)
{
	nlohmann::json nlBase{{"$ref", "#/unknown/keywords"}};
	nlohmann::json_schema::json_validator validator;

	JSONSV_TRY {
		validator.set_root_schema(nlBase); // this line will log the caught exception
	} JSONSV_CATCH(const std::exception &e) {
	#if defined(JSONSV_EXCEPTIONS)
		if (std::string("after all files have been parsed, '<root>' has still undefined references.") == e.what())
			return EXIT_SUCCESS;
	#endif
	}
	return EXIT_FAILURE;
}
