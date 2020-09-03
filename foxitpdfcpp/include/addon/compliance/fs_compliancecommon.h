
/**
 * Copyright (C) 2003-2020, Foxit Software Inc..
 * All Rights Reserved.
 *
 * http://www.foxitsoftware.com
 *
 * The following code is copyrighted and is the proprietary of Foxit Software Inc.. It is not allowed to
 * distribute any parts of Foxit PDF SDK to third party or public without permission unless an agreement
 * is signed between Foxit Software Inc. and customers to explicitly grant customers permissions.
 *
 * @file fs_compliancecommon.h
 * @brief Header file for compliance basic classes and methods.
 */

#ifndef FS_COMPLIANCEENGINE_H_
#define FS_COMPLIANCEENGINE_H_

#include "common/fs_common.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief Add-on namespace.
 */
namespace addon {
/**
 * @brief Compliance namespace.
 */
namespace compliance {
/**
 * Compliance module can be used to verify if a PDF file matches a specified industry standard version (e.g. one of PDF/A version)
 * or convert a PDF file to a specified industry standard version (e.g. one of PDF/A version).
 * Before initializing compliance engine and using any class or methods in this module, please ensure
 * Foxti PDF SDK has been initialized successfully by function @link common::Library::Initialize @endlink
 * with a key including "Compliance" module.
 *
 * @see @link common::Library @endlink
 */
class ComplianceEngine FS_FINAL : public Object{
 public:
  /**
   * @brief Initialize compliance engine.
   *
   * @details This should be called successfully before any other methods in compliance add-on module.
   *
   * @param[in] compliance_resource_folder_path  A complete path to compliance resource folder. This should not be an empty string.
   * @param[in] compliance_engine_unlockcode     The unlock code for compliance engine.
   *                                             <ul>
   *                                             <li> If an authorization key is used for Foxit PDF SDK, please
   *                                                  pass a valid unlock code string to initialize compliance engine.</li>
   *                                             <li> If a trial key is used for Foxit PDF SDK, this parameter will
   *                                                  be ignored. Just pass an empty string. </li>
   *                                             </ul>
   *
   * @return @link foxit::e_ErrSuccess @endlink means success.<br>
   *         @link foxit::e_ErrNoComplianceModuleRight @endlink means Foxit PDF SDK has not been initialized with
   *         a key including "Compliance" module.<br>
   *         @link foxit::e_ErrParam @endlink means parameter <i>compliance_resource_folder_path</i>is an empty string, or
   *         parameter <i>compliance_engine_unlockcode</i> is an empty string when an authorization key is used for
   *         Foxit PDF SDK.<br>
   *         @link foxit::e_ErrFilePathNotExist @endlink means parameter <i>compliance_resource_folder_path</i>
   *         does not exist or no library for compliance engine can be found under this folder.<br>
   *         @link foxit::e_ErrComplianceEngineInvalidUnlockCode @endlink means
   *         parameter <i>compliance_engine_unlockcode</i> is an invalid unlock code for compliance engine
   *         when an authorization key is used for Foxit PDF SDK.<br>
   *         For more information about error code values, please refer to values starting from
   *         @link foxit::e_ErrSuccess @endlink.
   *
   * @note If module "Compliance" is not defined in the license information which is used in function
   *       @link common::Library::Initialize @endlink, that means user has no right in using XFA related functions and
   *       this constructor will throw exception @link foxit::e_ErrNoComplianceModuleRight @endlink.
   */
  static ErrorCode Initialize(const wchar_t* compliance_resource_folder_path, const char* compliance_engine_unlockcode);

  /**
   * @brief Release compliance engine.
   *
   * @details This function can be called to release compliance engine when no need to use it any more
   *          before Foxit PDF SDK is released.
   *
   * @return None.
   */
  static void Release();

  /**
   * @brief Set a temp folder for compliance engine.
   *
   * @details Compliance engine may need to store several files for proper processing (e.g verifying or converting).
   *          User can use this function to set a temp folder. If no custom temp folder is set by this function,
   *          the default temp folder in system will be used.
   *
   * @param[in] temp_folder_path  A complete path to be set as temp folder. This should be a valid path and
   *                              should not be an empty string
   *
   * @return None.
   */
   static void SetTempFolderPath(const wchar_t* temp_folder_path);

  /**
   * @brief Set language for compliance engine.
   *
   * @details Setting a language to compliance engine will have affect on all the strings which are returned with
   *          @link compliance::ResultInformation @endlink or through callback class @link compliance::ProgressCallback @endlink.
   *          If no language name is set by this function, "English" will be used as default.
   *
   * @param[in] language  Language name. This cannot be an empty string and should be one of following language name:
   *                      "Czech", "Danish", "Dutch", "English", "French",
   *                      "Finnish", "German", "Italian", "Norwegian", "Polish",
   *                      "Portuguese", "Spanish", "Swedish",
   *                      "Chinese-Simplified", "Chinese-Traditional", "Japanese", "Korean".
   *                      For other language name, this function will do nothing.
   *
   * @return None.
   */
   static void SetLanguage(const char* language);
};

/**
 * This class represent a callback object to update the progress data to user.
 * All the pure virtual functions in this class are used as callback functions and should be implemented by user.
 */
class ProgressCallback {
 public:
  /**
   * @brief A callback function used to release current callback object itself.
   *
   * @return None.
   */
  virtual void Release() = 0;

  /**
   * @brief A callback function used to update current progress state data to user in order that user can update their progress bar.
   *
   * @param[in] current_rate          Current rate. It would be between 0 and 100 (inclusive). 100 means finished.
   * @param[in] current_state_string  A string that describing what current state is. This may be an empty string.
   *
   * @return None.
   */
  virtual void UpdateCurrentStateData(int current_rate, const WString& current_state_string) = 0;

 protected:
  ~ProgressCallback() {}
};

/**
 * This class represents a fixup data. Fixup data represents the data for a kind of fixup operation triggered during converting process.
 */
class FixupData : public Object {
 public:
  /**
   * @brief Enumeration for the state of a fixup data.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _FixupState {
    /** @brief A fixup succeeded. */
    e_FixupStateSuccess = 0,
    /** @brief A fixup failed. */
    e_FixupStateFailure = 1,
    /** @brief A fixup was not required. */
    e_FixupStateNotRequired = 2
  } FixupState;
  

  /** @brief Constructor. */
  FixupData()
    : used_count(0)
    , state(e_FixupStateNotRequired) {}

  /**
   * @brief Constructor, with another fixup data object.
   *
   * @param[in] other  Another fixup data object.
   */
  FixupData(const FixupData& other)
      : used_count(other.used_count)
      , state(other.state)
      , name(other.name)
      , comment(other.comment)
      , reasons(other.reasons) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another fixup data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  FixupData& operator = (const FixupData& other) {
    used_count = other.used_count;
    state = other.state;
    name = other.name;
    comment = other.comment;
    reasons = other.reasons;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another fixup data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const FixupData& other) const {
    bool is_equal = (used_count == other.used_count && state == other.state &&
                     name == other.name && comment == other.comment);
    if (is_equal) {
      for (int i=0; i<(int)reasons.GetSize(); i++) {
        if (reasons[i] != other.reasons[i]) {
          is_equal = false;
          break;
        }
      }
    }
    return is_equal;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another fixup data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const FixupData& other) const  {
    return !((*this) == other);
  }

  /** @brief Represents how many times the fixup operation for current data has been triggered during converting process. */
  uint32 used_count;
  /**
   * @brief Fixup state. Please refer to values starting from @link FixupData::e_FixupStateSuccess @endlink and
   *        this should be one of these values.
   */
  FixupState state;
  /** @brief Fixup rule name.*/
  WString name;
  /** @brief Fixup rule comment to explain more details about the rule. */
  WString comment;
  /** @brief Fixup reasons. This may be an empty array. The count of reasons is no more then <i>used_times</i>. */
  WStringArray reasons;
};

/**
 * This class represents a hit data. Hit data represents the data for a hit operation triggered during verifying or converting process.
 */
class HitData : public Object {
 public:
  /**
   * @brief Enumeration for check severity of a hit data.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _CheckSeverity {
    /** @brief Info severity. */
    e_CheckSeverityInfo = 1,
    /** @brief Warning severity. */
    e_CheckSeverityWarning = 2,
    /** @brief Error severity. */
    e_CheckSeverityError = 3
  } CheckSeverity;
  

  /** @brief Constructor. */
  HitData()
    : triggered_count(0)
    , severity(e_CheckSeverityInfo)
    , page_index(-1){}

  /**
   * @brief Constructor, with another hit data object.
   *
   * @param[in] other  Another hit data object.
   */
  HitData(const HitData& other)
      : triggered_count(other.triggered_count)
      , severity(other.severity)
      , name(other.name)
      , comment(other.comment)
      , trigger_values(other.trigger_values)
      , page_index(other.page_index) {}

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another hit data object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  HitData& operator = (const HitData& other) {
    triggered_count = other.triggered_count;
    severity = other.severity;
    name = other.name;
    comment = other.comment;
    trigger_values = other.trigger_values;
    page_index = other.page_index;
    return *this;
  }

  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another hit data object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const HitData& other) const {
    bool is_equal = (triggered_count == other.triggered_count && severity == other.severity &&
                     name == other.name && comment == other.comment && page_index == other.page_index);
    if (is_equal) {
      for (int i=0; i<(int)trigger_values.GetSize(); i++) {
        if (trigger_values[i] != other.trigger_values[i]) {
          is_equal = false;
          break;
        }
      }
    }
    return is_equal;
  }

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another hit data object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const HitData& other) const  {
    return !((*this) == other);
  }

  /** @brief Represents how many times the hit operation for current data has been triggered during verifying or converting process. */
  uint32 triggered_count;
  /**
   * @brief The check severity of current hit data. Please refer to values starting from @link HitData::e_CheckSeverityInfo @endlink and
   *        this should be one of these values.
   */
  CheckSeverity severity;
  /** @brief Hit rule name. */
  WString name;
  /** @brief Hit rule comment to explain more details about the rule. */
  WString comment;
  /** @brief Array of trigger values. The count of triggered values is no more then <i>triggered_count</i>.*/
  WStringArray trigger_values;
  /** @brief Page index, starting from 0. -1 means current hit data was hit in document level. */
  int page_index;
};

/**
 * This class represents the set of result information for verifying or converting process.
 * Fixup data or hit data can be retrieved from the result information.
 */
class ResultInformation FS_FINAL : public Base {
 public:
  /** @brief Constructor. */
  ResultInformation();
  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit ResultInformation(FS_HANDLE handle);
  /** @brief Destructor. */
  ~ResultInformation();
  /**
   * @brief Constructor, with another result information object.
   *
   * @param[in] other  Another ResultInformation object.
   */
  ResultInformation(const ResultInformation& other);

  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another result information object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  ResultInformation& operator = (const ResultInformation& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another result information object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const ResultInformation& other) const;

  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another result information object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const ResultInformation& other) const;

  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get count of fixup data.
   *
   * @return Count of fixup data.
   */
  int GetFixupDataCount() const;
  /**
   * @brief Get a fixup data.
   *
   * @param[in] index  Index of fixup data to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link ResultInformation::GetFixupDataCount @endlink.
   *
   * @return Fixup data.
   */
  FixupData GetFixupData(int index) const;

  /**
   * @brief Get count of hit data.
   *
   * @return Count of hit data.
   */
  int GetHitDataCount() const;
  /**
   * @brief Get a hit data.
   *
   * @param[in] index  Index of hit data to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link ResultInformation::GetHitDataCount @endlink.
   *
   * @return Hit data.
   */
  HitData GetHitData(int index) const;
};

}  // namespace compliance
}  // namespace addon
}  // namespace foxit

#endif  // FS_COMPLIANCEENGINE_H_

