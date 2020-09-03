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
 * @file fs_rendition.h
 * @brief Header file for PDF rendition related definitions and classes.
 */
#ifndef FS_RENDITION_H_
#define FS_RENDITION_H_

#include "common/fs_common.h"
#include "pdf/objects/fs_pdfobject.h"

/**
 * @brief Foxit namespace.
 *
 * @details All the definitions and classes of Foxit PDF SDK are defined within this namespace.
 */
namespace foxit {
/**
 * @brief PDF namespace.
 */
namespace pdf {
// forward declaration
class FileSpec;
class MediaPlayer;

/**
 * Rendition object is used as a media object that specifies what to play, how to play it and where to play it.
 * (For more details, please refer to <PDF Reference 1.7> P758 Section "9.1.2 Renditions", P762 "Media Renditions")
 */
class Rendition FS_FINAL : public Base {
 public:
  /**
   * @brief Enumeration for media option type.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Please refer to <PDF reference 1.7> P757 Section "9.1.1 Viability" for more details.
   */
  typedef enum _MediaOptionType {
    /** @brief Options defined in this type must be honored for rendition object to be considered viable. */
    e_MediaOptionMustBeHonored = 0,
    /** @brief Options defined in this type need only be honored in a "best effort" sense. */
    e_MediaOptionBestEffort = 1
  } MediaOptionType;
  
  /**
   * @brief Enumeration for PDF media player permission.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Media permission indicates the circumstances under which it is acceptable to write a temporary file
   *          in order to play a media clip. 
   */
  typedef enum _MediaPermission {
    /** @brief Never allowed. */
    e_MediaPermTempNever = 0,
    /** @brief Allowed only if the document permissions allow content extraction. */
    e_MediaPermTempExtract = 1,
    /** @brief Allowed only if the document permissions allow content extraction, including for accessibility purposes. */
    e_MediaPermTempAccess = 2,
    /** @brief Always allowed. */
    e_MediaPermTempAlways = 3
  } MediaPermission;
  
  /**
   * @brief Enumeration for PDF media player classified type.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _MediaPlayerType {
    /** @brief One of players in this type must be used in playing the associated media clip. */
    e_MediaPlayerMustUsed = 0,
    /** @brief Any of players in this type may be used in playing the associated media clip. */
    e_MediaPlayerAvailable = 1,
    /** @brief Players in this type must not be used in playing the associated media clip. */
    e_MediaPlayerNotUsed = 2
  } MediaPlayerType;
  
  /**
   * @brief Enumeration for the fit style.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Fit style (manner) specifies how the player should treat a visual media type that does not exactly
   *          fit the rectangle in which it plays.
   */
  typedef enum _MediaPlayerFitStyle {
    /**
   @brief The media's width and height are scaled while preserving the aspect ratio so that
          the media and play rectangles have the greatest possible intersection while still
          displaying all media content. Same as "meet" value of SMIL's fit attribute.
     */
    e_MediaPlayerFitStyleMeet = 0,
    /**
   @brief The media's width and height are scaled while preserving the aspect ratio so that
          the play rectangle is entirely filled, and the amount of media content that does not fit
          within the play rectangle is minimized. Same as "slice" value of SMIL's fit attribute.
     */
    e_MediaPlayerFitStyleSlice = 1,
    /**
   @brief The media's width and height are scaled independently so that the media and play rectangles are the same;
          the aspect ratio is not necessarily preserved. Same as "fill" value of SMIL's fit attribute.
     */
    e_MediaPlayerFitStyleFill = 2,
    /**
   @brief The media is not scaled. A scrolling user interface is provided if the media rectangle is wider or taller
          than the play rectangle. Same as "scroll" value of SMIL's fit attribute.
     */
    e_MediaPlayerFitStyleScroll = 3,
    /**
   @brief The media is not scaled. Only the portions of the media rectangle that intersect the play rectangle
          are displayed. Same as "hidden" value of SMIL's fit attribute.
     */
    e_MediaPlayerFitStyleHidden = 4,
    /** @brief Use the player's default setting (author has no preference). */
    e_MediaPlayerFitStyleDefault = 5
  } MediaPlayerFitStyle;
  
  /**
   * @brief Enumeration for the type of window that the media should play in.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _WindowType {
    /** @brief Window type: a floating window */
    e_WindowTypeFloating = 0,
    /** @brief Window type: a full-screen window that obscures all other windows */
    e_WindowTypeFullScreen = 1,
    /** @brief Window type: a hidden window */
    e_WindowTypeHidden = 2,
    /**
   @brief Window type: the rectangle occupied by the screen annotation which is associated with
          the rendition object.
     */
    e_WindowTypeAnnotRect = 3
  } WindowType;
  
  /**
   * @brief Enumeration for monitor specifier type.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Monitor specifier is used to specify which monitor in a multi-monitor system a floating or
   *          full-screen window should appear on. 
   */
  typedef enum _MonitorSpecifier {
    /** @brief The monitor that contains the largest section of the document window */
    e_MonitorSpecifierLargest = 0,
    /** @brief The monitor that contains the smallest section of the document window */
    e_MonitorSpecifierSmallest = 1,
    /** @brief Primary monitor. If no monitor is considered primary, use case 0 */
    e_MonitorSpecifierPrimary = 2,
    /** @brief Monitor with the greatest color depth */
    e_MonitorSpecifierGreatestColorDepth = 3,
    /** @brief Monitor with the greatest area (in pixels squared) */
    e_MonitorSpecifierGreatestArea = 4,
    /** @brief Monitor with the greatest height (in pixels) */
    e_MonitorSpecifierGreatestHeight = 5,
    /** @brief Monitor with the greatest width (in pixels) */
    e_MonitorSpecifierGreatestWidth = 6
  } MonitorSpecifier;
  
  /**
   * @brief Enumeration for the type of floating window's related window.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Related window type specifies the place to which the floating window should be positioned.
   */
  typedef enum _FloatingWindowRelatedWindowType {
    /** @brief The document window */
    e_FloatingWindowRelatedWindowDocument = 0,
    /** @brief The application window */
    e_FloatingWindowRelatedWindowApplication = 1,
    /** @brief The full virtual desktop */
    e_FloatingWindowRelatedWindowFullDesktop = 2,
    /** @brief Depends on monitor specifier. */
    e_FloatingWindowRelatedWindowMonitor = 3
  } FloatingWindowRelatedWindowType;
  
  /**
   * @brief Enumeration for resize type of floating window.
   *
   * @details Values of this enumeration should be used alone.
   */
  typedef enum _FloatingWindowResizeType {
    /** @brief May not be resized */
    e_FloatingWindowResizeTypeNo = 0,
    /** @brief May be resized only if aspect ratio is preserved */
    e_FloatingWindowResizeTypeAspectRatio = 1,
    /** @brief May be resized without preserving aspect ratio */
    e_FloatingWindowResizeTypeAnyway = 2
  } FloatingWindowResizeType;
  
  /**
   * @brief Enumeration for offscreen event type of floating window.
   *
   * @details Values of this enumeration should be used alone.<br>
   *          Offscreen event type is used to specifies what should occur if the floating window is
   *          positioned totally or partially offscreen (that is, not visible on any physical monitor).
   */
  typedef enum _FloatingWindowOffscreenEvent {
    /** @brief Nothing */
    e_FloatingWindowOffscreenEventNone = 0,
    /** @brief Move or resize */
    e_FloatingWindowOffscreenEventMoveResize = 1,
    /** @brief Consider the object non-viable */
    e_FloatingWindowOffscreenEventNonViable = 2
  } FloatingWindowOffscreenEvent;
  

  /**
   * @brief Constructor, with parameters.
   *
   * @param[in] pdf_doc         A valid PDF document object.
   * @param[in] rendition_dict  The PDF dictionary for a rendition object in PDF document represented
   *                            by parameter <i>pdf_doc</i>. If this is <b>NULL</b> that means to
   *                            construct a new rendition object in PDF document represented by parameter <i>pdf_obj</i>.
   *                            Default value: <b>NULL</b>.
   */
  Rendition(const PDFDoc& pdf_doc, objects::PDFDictionary* rendition_dict = NULL);
  /** @brief Destructor. */
  ~Rendition();

  /**
   * @brief Constructor, with another rendition object.
   *
   * @param[in] other  Another rendition object.
   */
  Rendition(const Rendition& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another rendition object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  Rendition& operator = (const Rendition& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another rendition object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const Rendition& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another rendition object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const Rendition& other) const;
  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;
  
  /**
   * @brief Get PDF dictionary of current object.
   *
   * @return The PDF dictionary.
   */
  objects::PDFDictionary* GetDict() const;

  /**
   * @brief Get the name.
   *
   * @details This name can be used for name tree lookup by JavaSript actions and can also be used in user interface.
   *
   * @return Name of current rendition object.
   */
  WString GetRenditionName() const;
  /**
   * @brief Get the name.
   *
   * @details This name can be used for name tree lookup by JavaSript actions and can also be used in user interface.
   *
   * @param[in] name  Name of current rendition object.
   *
   * @return None.
   */
  void SetRenditionName(const WString& name);

  /**
   * @brief Check if current rendition object contains a media clip.
   *
   * @return <b>true</b> means current rendition object contains a media clip, while <b>false</b> means
   *         current rendition object does not contain any media clip.
   */
  bool HasMediaClip() const;
  /**
   * @brief Get the name of the media clip, for use in user interface.
   *
   * @return Name of the media clip.
   */
  WString GetMediaClipName() const;
  /**
   * @brief Set the name of the media clip, for use in user interface.
   *
   * @param[in] name  Name string to be set for the media clip.
   *
   * @return None.
   */
  void SetMediaClipName(const WString& name);
  /**
   * @brief Get the file specification of the actual media data.
   *
   * @return A file specification object.
   */
  FileSpec GetMediaClipFile() const;
  /**
   * @brief Set the file specification of the actual media data.
   *
   * @details This property is necessary for a rendition object. And user is recommended to set the content type by
   *          function @link Rendition::SetMediaClipContentType @endlink after setting a new file specification.
   *
   * @param[in] file_specification  A file specification object.
   *
   * @return None.
   */
  void SetMediaClipFile(FileSpec file_specification);
 
  /**
   * @brief Get the content type (MIME type) of the media data.
   *
   * @details Content type specifies the type of the media data represented by file specification.
   *          The content type string should conform to the content type specification described in Internet RFC 2045,
   *          Multipurpose Internet Mail Extensions (MIME) Part One: Format of Internet Message Bodies.
   *
   * @return Content type (MIME type).
   */
  String GetMediaClipContentType() const;
  /**
   * @brief Set the content type (MIME type) of the media data.
   *
   * @details Content type specifies the type of the media data represented by file specification.
   *          The content type string should conform to the content type specification described in Internet RFC 2045,
   *          Multipurpose Internet Mail Extensions (MIME) Part One: Format of Internet Message Bodies.<br>
   *          User is recommended to set the content type when setting a new file specification by
   *          function @link Rendition::SetMediaClipFile @endlink.
   *
   * @param[in] content_type  Content type (MIME type).
   *
   * @return None.
   */
  void SetMediaClipContentType(const char* content_type);
  
  /**
   * @brief Get the media permission.
   *
   * @details Media permission indicates the circumstances under which it is acceptable to write a temporary file
   *          in order to play a media clip. 
   *
   * @return Media permission value. Please refer to values starting from @link Rendition::e_MediaPermTempNever @endlink and
   *         this would be one of these values.
   */
  MediaPermission GetPermission() const;
  /**
   * @brief Set the media permission.
   *
   * @details Media permission indicates the circumstances under which it is acceptable to write a temporary file
   *          in order to play a media clip. 
   *
   * @param[in] permission  Media permission value. Please refer to values starting from
   *                        @link Rendition::e_MediaPermTempNever @endlink and this should be one of these values.
   *
   * @return None.
   */
  void SetPermission(MediaPermission permission);

  /**
   * @brief Get the multi-language text array that provides alternate text descriptions for the media clip data
   *        in case it cannot be played.
   *
   * @details Strings in the multi-language text array are in pair: the first string (ASCII string) in each pair
   *          is language identifier and the second string is the description.
   *
   * @return The multi-language text array for description.
   */
  WStringArray GetMediaDescriptions() const;
  /**
   * @brief Set the multi-language text array that provides alternate text descriptions for the media clip data
   *        in case it cannot be played.
   *
   * @details Strings in the multi-language text array are in pair: the first string (ASCII string) in each pair
    *         is language identifier and the second string is the description.
   *
   * @param[in] description_array  A multi-language text array for description.
   *
   * @return None.
   */
  void SetMediaDescriptions(const WStringArray &description_array);

  /**
   * @brief Get the base URL.
   *
   * @details Base URL is an absolute URL which is used in resolving any relative URLs found within the media data.
   *
   * @return The base URL.
   */
  String GetMediaBaseURL() const;
  /**
   * @brief Set the base URL.
   *
   * @details Base URL is an absolute URL which is used in resolving any relative URLs found within the media data.
   *
   * @param[in] base_url  The base URL to set.
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetMediaBaseURL(const String& base_url, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the count of media player objects for specified type.
   *
   * @param[in] type  Media player type. Please refer to values starting from @link Rendition::e_MediaPlayerMustUsed @endlink
   *                  and this should be one of these values.
   *
   * @return The count of media player for specified type.
   */
  int GetMediaPlayerCount(MediaPlayerType type) const;
  /**
   * @brief Get a media player object by index for specified type.
   *
   * @param[in] type   Media player type. Please refer to values starting from @link Rendition::e_MediaPlayerMustUsed @endlink
   *                   and this should be one of these values.
   * @param[in] index  Index of the media player object to be retrieved. Valid range: from 0 to (<i>count</i>-1).
   *                   <i>count</i> is returned by function @link Rendition::GetMediaPlayerCount @endlink.
   *
   * @return A media player object.
   */
  MediaPlayer GetMediaPlayer(MediaPlayerType type, int index) const;
  /**
   * @brief Add a media player object for specified type.
   *
   * @details Usually, a media player object should be only be added to a rendition object with specified media player type.
   *          User is not recommended to add the same media player object to different renditions or
   *          different media player types of one rendition; otherwise unexpected issues (such as crash) may occur later.
   *          If user does not want to construct another media player and set same values, user can clone
   *          the dictionary of original media player object and use the cloned dictionary to
   *          construct another media player directly.
   *
   * @param[in] type    Media player type. Please refer to values starting from @link Rendition::e_MediaPlayerMustUsed @endlink
   *                    and this should be one of these values.
   * @param[in] player  A media player object to be added for specified type. If the media player has existed for
   *                    specified type, this function will return the index of the media player.
   *
   * @return Index of the input media player.
   */
  int AddMediaPlayer(MediaPlayerType type, const MediaPlayer &player);
  /**
   * @brief Remove a media player object for specified type.
   *
   * @param[in] type    Media player type. Please refer to values starting from @link Rendition::e_MediaPlayerMustUsed @endlink
   *                    and this should be one of these values.
   * @param[in] player  A media player object to be removed.
   *
   * @return None.
   */
  void RemoveMediaPlayer(MediaPlayerType type, const MediaPlayer &player);

  /**
   * @brief Get the volume that specifies the desired volume level as a percentage of recorded volume level.
   *
   * @return Volume value. 0 means mute.If no value for such property is defined in the rendition object, 
   *         100 would be returned by default.
   */
  int GetVolume() const;
  /**
   * @brief Set the volume that specifies the desired volume level as a percentage of recorded volume level.
   *
   * @param[in] volume    Volume value to set. 0 means mute. This value should not be negative.
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetVolume(int volume, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Check whether to display a player-specific controller user interface
   *        (for example, play/pause/stop controls) when playing.
   *
   * @return <b>true</b> means to display a player-specific controller user interface,
   *         while <b>false</b> means not to display such user interface.
   *         If no value for such property is defined in the rendition object, <b>false</b> would be returned by default.
   */
  bool IsControlBarVisible() const;
  /**
   * @brief Set the control bar visibility flag.
   *
   * @details Control bar visibility flag is used to decide whether to display a player-specific controller user interface
   *          (for example, play/pause/stop controls) when playing.
   *
   * @param[in] is_visible  <b>true</b> means to display a player-specific controller user interface,
   *                        while <b>false</b> means not to display such user interface.
   * @param[in] opt_type    Media option type. Please refer to values starting from
   *                        @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                        Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void EnableControlBarVisible(bool is_visible, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the fit style.
   *
   * @details Fit style (manner) specifies how the player should treat a visual media type that does not exactly
   *          fit the rectangle in which it plays. 
   *
   * @return Fit style value. Please refer to values starting from @link Rendition::e_MediaPlayerFitStyleMeet @endlink
   *         and this would be one of these values. If no value for such property is defined in the rendition object,
   *         @link Rendition::e_MediaPlayerFitStyleDefault @endlink would be returned by default.
   */
  MediaPlayerFitStyle GetFitStyle() const;
  /**
   * @brief Set the fit style.
   *
   * @details Fit style (manner) specifies how the player should treat a visual media type that does not exactly
   *          fit the rectangle in which it plays.
   *
   * @param[in] fit_style  Fit style value. Please refer to values starting from
   *                       @link Rendition::e_MediaPlayerFitStyleMeet @endlink and this should be one of these values.
   * @param[in] opt_type   Media option type. Please refer to values starting from
   *                       @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                       Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetFitStyle(MediaPlayerFitStyle fit_style, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the intrinsic duration.
   *
   * @return Intrinsic duration value. It would be:
   *         <ul>
   *         <li> -2: use intrinsic duration;</li>
   *         <li> -1: infinity duration;</li>
   *         <li> >= 0: explicit duration.</li>
   *         </ul>
   *         If no value for such property is defined in the rendition object, -2 would be returned by default.
   */
  int GetDuration() const;
  /**
   * @brief Set the intrinsic duration.
   *
   * @param[in] duration  Intrinsic duration value to set. It should be:
   *                      <ul>
   *                      <li> -2: use intrinsic duration;</li>
   *                      <li> -1: infinity duration;</li>
   *                      <li> >= 0: explicit duration.</li>
   *                      </ul>
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetDuration(int duration, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Check whether the media should automatically play when activated.
   *
   * @return <b>true</b> means the media should automatically play when activated,
   *         while <b>false</b> means the media should be initially paused when activated
   *         (for example, the first frame is displayed). Relevant only for media that may be paused.
   *         If no value for such property is defined in the rendition object, <b>true</b> would be returned by default.
   */
  bool IsAutoPlay() const;
  /**
   * @brief Check whether the media should automatically play when activated.
   *
   * @param[in] is_auto_play  <b>true</b> means the media should automatically play when activated,
   *                          while <b>false</b> means the media should be initially paused when activated
   *                          (for example, the first frame is displayed). Relevant only for media that may be paused.
   * @param[in] opt_type      Media option type. Please refer to values starting from
   *                          @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                          Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void EnableAutoPlay(bool is_auto_play, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the repeat count, similar to SMIL's repeatCount attribute.
   *
   * @return The repeat count.0 means repeat forever. If no value for such property is defined in the rendition object,
   *         1 would be returned by default.
   */
  int GetRepeatCount() const;
  /**
   * @brief Set the repeat count, similar to SMIL's repeatCount attribute.
   *
   * @param[in] count     The repeat count to be set. 0 means repeat forever. This value should not be negative value.
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetRepeatCount(int count, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the type of window that the media should play in.
   *
   * @return Windows type value. Please refer to @link Rendition::e_WindowTypeFloating @endlink
   *         values and it would be one of these values. If no value for such property is defined in the rendition object,
   *         @link Rendition::e_WindowTypeAnnotRect @endlink would be returned by default.
   */
  WindowType GetWindowType() const;
  /**
   * @brief Set the type of window that the media should play in.
   *
   * @param[in] window_type  Windows type value. Please refer to values starting from
   *                         @link Rendition::e_WindowTypeFloating @endlink and this should be one of these values.
   * @param[in] opt_type     Media option type. Please refer to values starting from
   *                         @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                         Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetWindowType(WindowType window_type, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the background color for the rectangle in which the media is being played.
   *
   * @return Background color. Format: 0xRRGGBB. The returned value 0xFFFFFF may also mean that no value for such property
   *         is defined in the rendition object.
   */
  RGB GetBackgroundColor() const;
  /**
   * @brief Set the background color for the rectangle in which the media is being played.
   *
   * @param[in] color     Background color to set. Format: 0xRRGGBB.
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetBackgroundColor(RGB color, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the background opacity. (ignored for full-screen and hidden windows)
   *
   * @return Background opacity. Valid range: 0.0 to 1.0. 
   *         0.0 means full transparency and 1.0 means full opaque.
   *         If no value for such property is defined in the rendition object,
   *         1.0 would be returned by default.
   */
  float GetBackgroundOpacity() const;
  /**
   * @brief Set the background opacity. (ignored for full-screen and hidden windows)
   *
   * @param[in] opacity   Background opacity. Valid range: 0.0 to 1.0.
   *                      0.0 means full transparency and 1.0 means full opaque.
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetBackgroundOpacity(float opacity, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the monitor specifier type value.
   *
   * @details Monitor specifier is used to specify which monitor in a multi-monitor system a floating or
   *          full-screen window should appear on. 
   *
   * @return Monitor specifier type value. Please refer to values starting from
   *         @link Rendition::e_MonitorSpecifierLargest @endlink and this would be one of these values.
   *         If no value for such property is defined in the rendition object,
   *         @link Rendition::e_MonitorSpecifierLargest @endlink would be returned by default.
   */
  MonitorSpecifier GetMonitorSpecifier() const;
  /**
   * @brief Set the monitor specifier type value.
   *
   * @details Monitor specifier is used to specify which monitor in a multi-monitor system a floating or
   *          full-screen window should appear on. 
   *
   * @param[in] monitor_specifier  Monitor specifier type value. Please refer to values starting from
   *                               @link Rendition::e_MonitorSpecifierLargest @endlink and this should be one of these values.
   * @param[in] opt_type           Media option type. Please refer to values starting from
   *                               @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                               Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetMonitorSpecifier(MonitorSpecifier monitor_specifier, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the width of floating window, in pixels.
   *
   * @details This property is necessary when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @return Width of floating window, in pixels.
   */
  int GetFloatingWindowWidth() const;
  /**
   * @brief Get the height of floating window, in pixels.
   *
   * @details This property is necessary when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @return Height of floating window, in pixels.
   */
  int GetFloatingWindowHeight() const;
  /**
   * @brief Set the size of floating window, in pixels.
   *
   * @details This property is necessary when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @param[in] width     Width of floating window, in pixels. This value should be larger than 0.
   * @param[in] height    Height of floating window, in pixels. This value should be larger than 0.
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetFloatingWindowSize(int width, int height, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the window relative type.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.<br>
   *          Related window type specifies the place to which the floating window should be positioned.
   *
   * @return Related window type. Please refer to values starting from
   *         @link Rendition::e_FloatingWindowRelatedWindowDocument @endlink and this would be one of these values.
   *         this would be one of these values. If no value for such property is defined in the rendition object,
   *         @link Rendition::e_FloatingWindowRelatedWindowDocument @endlink would be returned by default.
   */
  FloatingWindowRelatedWindowType GetFloatingWindowRelatedWindowType() const;
  /**
   * @brief Set the window relative type.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.<br>
   *          Related window type specifies the place to which the floating window should be positioned.
   *
   * @param[in] window_type  Related window type. Please refer to values starting from
   *                         @link Rendition::e_FloatingWindowRelatedWindowDocument @endlink and
   *                         this should be one of these values.
   * @param[in] opt_type     Media option type. Please refer to values starting from
   *                         @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                         Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetFloatingWindowRelatedWindowType(FloatingWindowRelatedWindowType window_type, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the position where floating window should be positioned to the related window.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.<br>
   *          Window relative specifies the place to which the floating window should be positioned.
   *
   * @return Position value. Please refer to values starting from @link common::e_PosTopLeft @endlink and
   *         this would be one of these values. If no value for such property is defined in the rendition object,
   *         @link common::e_PosCenter @endlink would be returned by default.
   */
  common::Position GetFloatingWindowPosition() const;
  /**
   * @brief Set the position where floating window should be positioned to the related window.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.<br>
   *          Window relative specifies the place to which the floating window should be positioned.
   *
   * @param[in] position  Window relative type. Please refer to values starting from
   *                      @link Rendition::e_FloatingWindowRelatedWindowDocument @endlink and
   *                      this should be one of these values.
   * @param[in] opt_type  Media option type. Please refer to values starting from 
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetFloatingWindowPosition(common::Position position, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the event type which specifies what should occur if the floating window is
   *        positioned totally or partially offscreen (that is, not visible on any physical monitor).
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @return Event type for offscreen situation of floating window. Please refer to values starting from
   *         @link Rendition::e_FloatingWindowOffscreenEventNone @endlink and this would be one of these values.
   *         If no value for such property is defined in the rendition object,
   *         @link Rendition::e_FloatingWindowOffscreenEventMoveResize @endlink would be returned by default.
   */
  FloatingWindowOffscreenEvent GetFloatingWindowOffscreenEvent() const;
  /**
   * @brief Set the event type which specifies what should occur if the floating window is
   *        positioned totally or partially offscreen (that is, not visible on any physical monitor).
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @param[in] offscreen_event  Event type for offscreen situation of floating window. Please refer to values
   *                             starting from @link Rendition::e_FloatingWindowOffscreenEventNone @endlink and
   *                             this should be one of these values.
   * @param[in] opt_type         Media option type. Please refer to values starting from
   *                             @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                             Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetFloatingWindowOffscreenEvent(FloatingWindowOffscreenEvent offscreen_event, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Check if the floating window should have a title bar.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @return <b>true</b> means the floating window should have a title bar, while <b>false</b> means
   *         the floating window does not need to have a title bar. If no value for such property is defined in the rendition object,
   *         <b>true</b> would be returned by default.
   */
  bool HasFloatingWindowTitleBar() const;
  /**
   * @brief Set flag to specify if the floating window should have a title bar.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @param[in] is_visible  <b>true</b> means the floating window should have a title bar, while <b>false</b> means
   *                        the floating window does not need to have a title bar..
   * @param[in] opt_type    Media option type. Please refer to values starting from
   *                        @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                        Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void EnableFloatingWindowTitleBar(bool is_visible, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Check if the floating window should include user interface elements that allow a user to
   *        close a floating window.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @return <b>true</b> means the floating window should include user interface elements that allow a user to
   *         close a floating window, while <b>false</b> means the floating window does not need to
   *         include such user interface element. If no value for such property is defined in the rendition object,
   *         <b>true</b> would be returned by default.
   */
  bool HasFloatingWindowCloseButton() const;
  /**
   * @brief Set the flag to specify if the floating window should include user interface elements that allow a user to
   *        close a floating window.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @param[in] is_visible  <b>true</b> means the floating window should include user interface elements that
   *                        allow a user to close a floating window, while <b>false</b> means
   *                        the floating window does not need to include such user interface element.
   * @param[in] opt_type    Media option type. Please refer to values starting from
   *                        @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                        Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void EnableFloatingWindowCloseButton(bool is_visible, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the resize type which specifies whether the floating window may be resized by a user.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @return Resize type. Please refer to values starting from @link Rendition::e_FloatingWindowResizeTypeNo @endlink and
   *         this would be one of these values. If no value for such property is defined in the rendition object,
   *         @link Rendition::e_FloatingWindowResizeTypeNo @endlink would be returned by default.
   */
  FloatingWindowResizeType GetFloatingWindowResizeType() const;
  /**
   * @brief Set the resize type which specifies whether the floating window may be resized by a user.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.
   *
   * @param[in] resize_type  Resize type. Please refer to values starting from
   *                         @link Rendition::e_FloatingWindowResizeTypeNo @endlink and
   *                         this should be one of these values.
   * @param[in] opt_type     Media option type. Please refer to values starting from
   *                         @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                         Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetFloatingWindowResizeType(FloatingWindowResizeType resize_type, MediaOptionType opt_type = e_MediaOptionBestEffort);

  /**
   * @brief Get the multi-language text array which provides text to display on the floating window's title bar.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.<br>
   *          Strings in the multi-language text array are in pair: the first string (ASCII string) in each pair
   *          is language identifier and the second string is the caption.
   *
   * @return A string array that represents multi-language text array.
   */
  WStringArray GetFloatingWindowTitles() const;
  /**
   * @brief Set the multi-language text array which provides text to display on the floating window's title bar.
   *
   * @details This property is only useful when the windows type is @link Rendition::e_WindowTypeFloating @endlink.<br>
   *          Strings in the multi-language text array are in pair: the first string (ASCII string) in each pair
   *          is language identifier and the second string is the caption.
   *
   * @param[in] titles    A string array that represents multi-language text array.
   * @param[in] opt_type  Media option type. Please refer to values starting from
   *                      @link Rendition::e_MediaOptionMustBeHonored @endlink and this should be one of these values.
   *                      Default value: @link Rendition::e_MediaOptionBestEffort @endlink.
   *
   * @return None.
   */
  void SetFloatingWindowTitles(const WStringArray& titles, MediaOptionType opt_type = e_MediaOptionBestEffort);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit Rendition(FS_HANDLE handle =  NULL);
};

/**
 * Class @link MediaPlayer @endlink provides methods to access to information regarding a specific media player.
 */
class MediaPlayer FS_FINAL : public Base {
 public:
  /**
   * @brief Constructor, with parameters.
   *
   * @details Usually, a media player object should be only be added to a rendition object with specified media player type.
   *          User is not recommended to add the same media player object to different renditions or
   *          different media player types of one rendition; otherwise unexpected issues (such as crash) may occur later.
   *          If user does not want to construct another media player and set same values, user can clone
   *          the dictionary of original media player object and use the cloned dictionary to
   *          construct another media player directly.
   *
   * @param[in] media_player_dict  The PDF dictionary for a media player object. If this is <b>NULL</b> that means to
   *                               construct a new media player object. Default value: <b>NULL</b>.
   */
  MediaPlayer(objects::PDFDictionary* media_player_dict = NULL);
  /** @brief Destructor. */
  ~MediaPlayer();

  /**
   * @brief Constructor, with another media player object.
   *
   * @param[in] other  Another media player object.
   */
  MediaPlayer(const MediaPlayer& other);
  /**
   * @brief Assign operator.
   *
   * @param[in] other  Another media player object, whose value would be assigned to current object.
   *
   * @return Reference to current object itself.
   */
  MediaPlayer& operator = (const MediaPlayer& other);
  /**
   * @brief Equal operator.
   *
   * @param[in] other  Another media player object. This function will check if current object is equal to this one.
   *
   * @return <b>true</b> means equal, while <b>false</b> means not equal.
   */
  bool operator == (const MediaPlayer& other) const;
  /**
   * @brief Not equal operator.
   *
   * @param[in] other  Another media player object. This function will check if current object is not equal to this one.
   *
   * @return <b>true</b> means not equal, while <b>false</b> means equal.
   */
  bool operator != (const MediaPlayer& other) const;
  /**
   * @brief Check whether current object is empty or not.
   *
   * @details When the current object is empty, that means current object is useless.
   *
   * @return <b>true</b> means current object is empty, while <b>false</b> means not.
   */
  bool IsEmpty() const;

  /**
   * @brief Get the PDF dictionary of current object.
   *
   * @return PDF dictionary of current object.
   */
  objects::PDFDictionary* GetDict() const;
  /**
   * @brief Get software URI that identifies a piece of software.
   *
   * @details For more details, please refer to <PDF reference 1.7> P780 "Software URIs".
   *
   * @return Software URI.
   */
  String GetSoftwareURI() const;
  /**
   * @brief Get software URI that identifies a piece of software.
   *
   * @details This property is necessary for a media player object. For more details, please refer to
   *          <PDF reference 1.7> P780 "Software URIs".
   *
   * @param[in] uri  Software URI. It should not be an empty string.
   *
   * @return None.
   */
  void SetSoftwareURI(const String& uri);

  /**
   * @brief Get the string array that represents operating system identifiers.
   *
   * @details Operating system identifiers in this array indicate which operating systems this object applies to.
   *          The defined values are the same as those defined for SMIL 2.0's systemOperatingSystem attribute.
   *          There may not be multiple copies of the same identifier in the array. 
   *
   * @return A string array that represents operating system identifiers. 
   *         An empty array is considered to represent all operating systems. 
   */
  StringArray GetOSIdentifiers() const;
  /**
   * @brief Set the string array that represents operating system identifiers.
   *
   * @details Operating system identifiers in this array indicate which operating systems this object applies to.
   *          The defined values are the same as those defined for SMIL 2.0's systemOperatingSystem attribute.
   *          There may not be multiple copies of the same identifier in the array. 
   *
   * @param[in] identifier_array  A string array that represents operating system identifiers.
   *                              An empty array is considered to represent all operating systems.
   *
   * @return None.
   */
  void SetOSIdentifiers(const StringArray& identifier_array);

  // User is strongly recommended NOT to use this method; otherwise unknown situation may occur.
  explicit MediaPlayer(FS_HANDLE handle);
};
}  // namespace pdf
}  // namespace foxit

#endif  // FS_RENDITION_H_

