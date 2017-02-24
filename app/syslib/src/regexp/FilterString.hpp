#ifndef FILTER_STRING_HPP_
#define FILTER_STRING_HPP_
/**
 *  @file     FilterString.hpp
 *  @brief    Emplementation various regular expression.
 *  @author   Gerasimov A.S.
 */
namespace regexp {

/**
 * Type describes simple filter rules for string.
 */
class FilterString {
public:
	/**
	 * Filter rules type.
	 */
	enum FilterType {
		TYPE_NONE,
		TYPE_BINCHAR,
		TYPE_DECCHAR,
		TYPE_HEXCHAR,
		TYPE_LETTERS,
		TYPE_CUSTOM
	};

	/**
	 * @brief
	 * Create filter object.
	 *
	 * @param : [in] filter type.
	 * @param : [in] point to users custom filter (optional).
	 */
	FilterString( enum FilterType type, const char *custom=NULL ) :
		filter_type_(type),
		custom_filter_string_(custom)
	{
		;
	}

	/**
	 * @brief
	 * Check input char to template matching.
	 *
	 * @param c : [in] input char for identification.
	 *
	 * @retval true  : [success] input char matching to etalon template.
	 * @retval false : [failed] not matching.
	 */
	bool match ( char c );

	/**
	 * @brief
	 * Check input string to tempalte matching.
	 *
	 * @param pstr : [in] input string for identification.
	 *
	 * @retval true  : [success] input string matching to etalon template.
	 * @retval false : [failed] not matching.
	 */
	bool match ( const char *pstr );

private:
	enum FilterType filter_type_;
	/*
	 * Point to users custom filter.
	 */
	const char *custom_filter_string_;
};

} /* namespace regexp */

#endif  /* FILTER_STRING_HPP_ */
