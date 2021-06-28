#include <nlohmann/json-schema.hpp>
#include <json-schema-include.hpp>

#include <iostream>

int main(void)
{
	nlohmann::json schema_json{{"type", "number"}};
	nlohmann::json_schema::json_validator validator;

	validator.set_root_schema(schema_json);

	validator.validate(1);
	JSONSV_TRY {
		validator.validate("\"1\"");
	} JSONSV_CATCH(const std::exception &e) {
	#if defined(JSONSV_EXCEPTIONS)
		std::cerr << "expected exception: " << e.what() << "\n";
	#endif
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
