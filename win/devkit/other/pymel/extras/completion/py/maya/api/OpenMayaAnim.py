
class MAnimControl(object):
    """
    Control over animation playback and values
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def animationEndTime(self, *args, **kwargs):        """        animationEndTime() -> MTime                Return an MTime specifying the last frame of the animation, as specified by the Maya user in the Range Slider UI.        """        pass


    def animationStartTime(self, *args, **kwargs):        """        animationStartTime() -> MTime                Return an MTime specifying the first frame of the animation, as specified by the Maya user in the Range Slider UI.        """        pass


    def autoKeyMode(self, *args, **kwargs):        """        autoKeyMode() -> bool                Return the autoKeyMode.        """        pass


    def currentTime(self, *args, **kwargs):        """        currentTime() -> MTime                Return an MTime instance containing the current animation frame.        """        pass


    def globalInTangentType(self, *args, **kwargs):        """        globalInTangentType() -> int                Return the current global in tangent type.        """        pass


    def globalOutTangentType(self, *args, **kwargs):        """        globalOutTangentType() -> int                Return the current global out tangent type.        """        pass


    def isPlaying(self, *args, **kwargs):        """        isPlaying() -> bool                Return a value indicating whether Maya is currently playing the animation        """        pass


    def isScrubbing(self, *args, **kwargs):        """        isScrubbing() -> bool                Return a value indicating whether interactive scrubbing is occuring while Maya is not currently playing an animation.        """        pass



    kPlaybackLoop = 1


    kPlaybackOnce = 0


    kPlaybackOscillate = 2


    kPlaybackViewActive = 1


    kPlaybackViewAll = 0

    def maxTime(self, *args, **kwargs):        """        maxTime() -> MTime                Return an MTime specifying the last frame of the current playback time range.        """        pass


    def minTime(self, *args, **kwargs):        """        minTime() -> MTime                Return an MTime specifying the first frame of the current playback time range.        """        pass


    def playBackward(self, *args, **kwargs):        """        playBackward() -> None                Start playing the current animation backwards.        """        pass


    def playForward(self, *args, **kwargs):        """        playForward() -> None                Start playing the current animation forwards.        """        pass


    def playbackBy(self, *args, **kwargs):        """        playbackBy() -> float                Return a float specifying the increment between times viewed during the playing of the animation.        """        pass


    def playbackMode(self, *args, **kwargs):        """        playbackMode() -> int                Return the playback mode currently in effect:          MAnimControl.kPlaybackOnce         Play once then stop.          MAnimControl.kPlaybackLoop         Play continuously.          MAnimControl.kPlaybackOscillate    Play forwards, then backwards continuously.        """        pass


    def playbackSpeed(self, *args, **kwargs):        """        playbackSpeed() -> float                Return the speed with with to play the animation.        """        pass


    def setAnimationEndTime(self, *args, **kwargs):        """        setAnimationEndTime(MTime) -> None                Set the value of the last frame in the animation.        """        pass


    def setAnimationStartEndTime(self, *args, **kwargs):        """        setAnimationStartEndTime(MTime, MTime) -> None                Set the values of the first and last frames in the animation.        """        pass


    def setAnimationStartTime(self, *args, **kwargs):        """        setAnimationStartTime(MTime) -> None                Set the value of the first frame in the animation.        """        pass


    def setAutoKeyMode(self, *args, **kwargs):        """        setAutoKeyMode(bool) -> None                Set the autoKeyMode.        """        pass


    def setCurrentTime(self, *args, **kwargs):        """        setMinTime(MTime) -> None                Set the current animation frame.        """        pass


    def setGlobalInTangentType(self, *args, **kwargs):        """        setGlobalInTangentType(int) -> None                Set the current global in tangent type        """        pass


    def setGlobalOutTangentType(self, *args, **kwargs):        """        setGlobalOutTangentType(int) -> None                Set the current global out tangent type.        """        pass


    def setMaxTime(self, *args, **kwargs):        """        setMaxTime(MTime) -> None                Set the value of the last frame of the current playback time range.        """        pass


    def setMinMaxTime(self, *args, **kwargs):        """        setMinMaxTime(MTime, MTime) -> None                Set the values of the first and last frames of the playback time range.        """        pass


    def setMinTime(self, *args, **kwargs):        """        setMinTime(MTime) -> None                Set the value of the first frame of the current playback time range.        """        pass


    def setPlaybackBy(self, *args, **kwargs):        """        setPlaybackBy(float) -> None                Specify the increment between times viewed during the playing of the animation.        """        pass


    def setPlaybackMode(self, *args, **kwargs):        """        setPlaybackMode(int) -> None                Set the current playback mode.        """        pass


    def setPlaybackSpeed(self, *args, **kwargs):        """        setPlaybackSpeed(float) -> None                Set the desired speed factor at which the animation will play back.        """        pass


    def setViewMode(self, *args, **kwargs):        """        setViewMode(int) -> None                Set the current viewing mode.        Controls whether the animation is run in only the active view, or simultaneously in all views.        """        pass


    def setWeightedTangents(self, *args, **kwargs):        """        setWeightedTangents(bool) -> None                Sets whether or not the tangents on the Anim Curve are weighted.        """        pass


    def stop(self, *args, **kwargs):        """        stop() -> None                Stop playing the current animation.        """        pass


    def viewMode(self, *args, **kwargs):        """        viewMode() -> int                Return the viewing mode currently in effect:          MAnimControl.kPlaybackViewAll      Playback in all views.          MAnimControl.kPlaybackViewActive   Playback in only the active view.        """        pass


    def weightedTangents(self, *args, **kwargs):        """        weightedTangents() -> bool                Determine whether or not the tangents on the Anim Curve are weighted.        """        pass



class MAnimCurveChange(object):
    """
    Anim curve change cache.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def redoIt(self, *args, **kwargs):        """        Redo all of the Anim Curve changes in this cache.        """        pass


    def undoIt(self, *args, **kwargs):        """        Undo all of the Anim Curve changes in this cache.        """        pass



class MAnimCurveClipboard(object):
    """
    Provides control over the animation clipboard.
    
    __init__()
    Initializes a new, empty MAnimCurveClipboard object.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def clear(self, *args, **kwargs):        """        clear() -> self                Clears the clipboard.        """        pass


    def clipboardItems(self, *args, **kwargs):        """        clipboardItems() -> MAnimCurveClipboardItemArray                Returns the clipboard items.        """        pass


    @property
    def endTime(self, *args, **kwargs):        """        The end time of the clipboard.        """        pass


    @property
    def endUnitlessInput(self, *args, **kwargs):        """        The end unitless input of the clipboard.        """        pass


    @property
    def isEmpty(self, *args, **kwargs):        """        Whether the clipboard is empty.        """        pass


    def set(self, *args, **kwargs):        """        set( clipboard ) -> self        set( items ) -> self        set( items, startTime, endTime, startUnitlessInput, endUnitlessInput, strictValidation=True ) -> self                Sets the content of the clipboard.        items may be either an MAnimClipboardItemArray or a sequence of MAnimClipboardItems.        """        pass


    @property
    def startTime(self, *args, **kwargs):        """        The start time of the clipboard.        """        pass


    @property
    def startUnitlessInput(self, *args, **kwargs):        """        The start unitless input of the clipboard.        """        pass


    def theAPIClipboard(self, *args, **kwargs):        """        Provides control over the animation clipboard.                __init__()        Initializes a new, empty MAnimCurveClipboard object.        """        pass



class MAnimCurveClipboardItem(object):
    """
    This class provides a wrapper for a clipboard item.
    
    __init__()
    Initializes a new, empty MAnimCurveClipboardItem object.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    @property
    def animCurve(self, *args, **kwargs):        """        The anim curve.        """        pass


    def animCurveType(self, *args, **kwargs):        """        animCurveType() -> MFnAnimCurve.AnimCurveType                Returns the type of the items anim curve.                """        pass


    @property
    def fullAttributeName(self, *args, **kwargs):        """        The full attribute name.        """        pass


    def getAddressingInfo(self, *args, **kwargs):        """        getAddressingInfo() -> (unsigned int, unsigned int, unsigned int)                Returns the addressing information for this clipboard item        as (rowCount, childCount, attributeCount).        """        pass


    @property
    def leafAttributeName(self, *args, **kwargs):        """        The leaf attribute name.        """        pass


    @property
    def nodeName(self, *args, **kwargs):        """        The node name.        """        pass


    def setAddressingInfo(self, *args, **kwargs):        """        setAddressingInfo(rowCount, childCount, attributeCount) -> self                Sets the addressing information for this clipboard item.        """        pass


    def setAnimCurve(self, *args, **kwargs):        """        setAnimCurve(object) -> self                Sets the anim curve MObject.        """        pass


    def setNameInfo(self, *args, **kwargs):        """        setNameInfo(nodeName, fullName, leafName) -> self                Sets the name information for this clipboard item.        """        pass



class MAnimCurveClipboardItemArray(object):
    """
    Array of MAnimCurveClipboardItem values.
    """

    def __add__(self, *args, **kwargs):        """        x.__add__(y) <==> x+y        """        pass


    def __contains__(self, *args, **kwargs):        """        x.__contains__(y) <==> y in x        """        pass


    def __delitem__(self, *args, **kwargs):        """        x.__delitem__(y) <==> del x[y]        """        pass


    def __delslice__(self, *args, **kwargs):        """        x.__delslice__(i, j) <==> del x[i:j]                                      Use of negative indices is not supported.        """        pass


    def __getitem__(self, *args, **kwargs):        """        x.__getitem__(y) <==> x[y]        """        pass


    def __getslice__(self, *args, **kwargs):        """        x.__getslice__(i, j) <==> x[i:j]                                      Use of negative indices is not supported.        """        pass


    def __iadd__(self, *args, **kwargs):        """        x.__iadd__(y) <==> x+=y        """        pass


    def __imul__(self, *args, **kwargs):        """        x.__imul__(y) <==> x*=y        """        pass


    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __len__(self, *args, **kwargs):        """        x.__len__() <==> len(x)        """        pass


    def __mul__(self, *args, **kwargs):        """        x.__mul__(n) <==> x*n        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __rmul__(self, *args, **kwargs):        """        x.__rmul__(n) <==> n*x        """        pass


    def __setitem__(self, *args, **kwargs):        """        x.__setitem__(i, y) <==> x[i]=y        """        pass


    def __setslice__(self, *args, **kwargs):        """        x.__setslice__(i, j, y) <==> x[i:j]=y                                      Use  of negative indices is not supported.        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def append(self, *args, **kwargs):        """        Add a value to the end of the array.        """        pass


    def clear(self, *args, **kwargs):        """        Remove all elements from the array.        """        pass


    def copy(self, *args, **kwargs):        """        Replace the array contents with that of another or of a compatible Python sequence.        """        pass


    def insert(self, *args, **kwargs):        """        Insert a new value into the array at the given index.        """        pass


    def remove(self, *args, **kwargs):        """        Remove an element from the array.        """        pass


    def setLength(self, *args, **kwargs):        """        Grow or shrink the array to contain a specific number of elements.        """        pass


    @property
    def sizeIncrement(self, *args, **kwargs):        """        Number of elements by which to grow the array when necessary.        """        pass



class MAnimMessage(MMessage):
    """
    Class used to register callbacks for anim related messages.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def addAnimCurveEditedCallback(self, *args, **kwargs):        """        addAnimCurveEditedCallback(function, clientData=None) -> id                This method registers a callback that is called whenever an        AnimCurve is edited.                 * function - callable which will be passed a MObjectArray object containing           an array of AnimCurves which have been edited, and the clientData object         * clientData - User defined data passed to the callback function                 * return: Identifier used for removing the callback.        """        pass


    def addAnimKeyframeEditCheckCallback(self, *args, **kwargs):        """        addAnimKeyframeEditCheckCallback(function, clientData=None) -> id                This method registers a callback that is used by the setKeyframe command        to allow a user to consider the set keyframe request and cancel it if        needed. The callback method should return False to abort the keyframe        setting.                 * function - callable which will be passed a MPlug indicating the           plug being keyframed and the clientData object.           Return False to abort the keyframe action, otherwise return True         * clientData - User defined data passed to the callback function                 * return: Identifier used for removing the callback.        """        pass


    def addAnimKeyframeEditedCallback(self, *args, **kwargs):        """        addAnimKeyframeEditedCallback(function, clientData=None) -> id                This method registers a callback that is called whenever an        a group of keys are modified.  The callback is invoked once per        atomic change to single or group of keyframes. For example, if        a user selects a group 5 of keys and moves them 5 units in the value        axis, then a single callback event will be invoked with a MObject        for each of the 5 keyframes.  The MObjects can then be used in the        MFnKeyframeDelta function set. Refer to MFnKeyframeDelta function set        documentation for more info.                 * function - callable which will be passed a MObjectArray object containing           an array of keyframes that were edited, and the clientData object         * clientData - User defined data passed to the callback function                 * return: Identifier used for removing the callback.        """        pass


    def addDisableImplicitControlCallback(self, *args, **kwargs):        """        addDisableImplicitControlCallback(function, clientData=None) -> id                This method registers a callback that is called from bakeResults        command after baking operation is completed, if disableImplicitControl        is enabled. One example usage of this callback is to create the anim curve        that is used to drive Maya rigidbodys bakeSimulationIndex, which defines        if the rigid body should take its input from anim curve or rigid body         simulation.                 * function - callable which will be passed a MPlugArray containing the baked plugs           (they can be replaced but must have the same number of plugs), a MDGModifier used           if bakeResults command is undone or redone and the clientData object.         * clientData - User defined data passed to the callback function                 * return: Identifier used for removing the callback.        """        pass


    def addNodeAnimKeyframeEditedCallback(self, *args, **kwargs):        """        addNodeAnimKeyframeEditedCallback(animNode, function, clientData=None) -> id                This method registers a callback that is called whenever an a        group of keys are modified.  The callback is invoked once per        atomic change to single or group of keyframes on the specified        animation curve node. For example, if a user selects a group 5        of keys and moves them 5 units in the value axis, then a single        callback event will be invoked with a MObject for each of the 5        keyframes.  The MObjects can then be used in the MFnKeyframeDelta        function set. Refer to MFnKeyframeDelta function set documentation        for more info.                 * animNode (MObject) - the param curve node you want to watch.         * function - callable which will be passed a MObject indicating the           edited animation node, a MObjectArray containing an array of keyframes           that were edited and the clientData object.         * clientData - User defined data passed to the callback function                 * return: Identifier used for removing the callback.        """        pass


    def addPostBakeResultsCallback(self, *args, **kwargs):        """        addPostBakeResultsCallback(function, clientData=None) -> id                This method registers a callback that is called from bakeResults        command after the simulation. If the plugArray is replaced, then        the anim curves created from baking will be connected to the new        plugs.                 * function - callable which will be passed a MPlugArray containing the baked           plugs to which the resulting anim curves will be connected (they can be           replaced but must have the same number of plugs),a MDGModifier used if           bakeResults command is undone or redone and the clientData object.         * clientData - User defined data passed to the callback function                 * return: Identifier used for removing the callback.        """        pass


    def addPreBakeResultsCallback(self, *args, **kwargs):        """        addPreBakeResultsCallback(function, clientData=None) -> id                This method registers a callback that is called from bakeResults        command before the simulation. One example usage is handle the runup to        the first frame in a dynamic system. If plugArray is set to zero        length in the callback, the baking will be aborted.                 * function - callable which will be passed a MPlugArray containing the plugs           to be baked (they can be replaced but must have the same number of plugs)           ,a MDGModifier used if bakeResults command is undone or redone and the           clientData object.         * clientData - User defined data passed to the callback function                 * return: Identifier used for removing the callback.        """        pass


    def currentCallbackId(self, *args, **kwargs):        """        currentCallbackId() -> id                Returns the callback ID of the currently executing callback. If called        outside of a callback, an invalid MCallbackId and failed status will        be returned.        """        pass


    def flushAnimKeyframeEditedCallbacks(self, *args, **kwargs):        """        flushAnimKeyframeEditedCallbacks() -> None                Animation keyframe edited callbacks are queued to only be issued on an        idle event. There may be times when it is desired to issue the callback        at a specific time. This method provides this functionality. It will        flush all animation keyframe edited callbacks and force them to issue        their callbacks with the data contained within.        """        pass



    kDefaultAction = 0


    kDoAction = 2


    kDoNotDoAction = 1

    def nodeCallbacks(self, *args, **kwargs):        """        nodeCallbacks(node) -> ids                Returns a list of callback IDs registered to a given node.                 * node (MObject) - Node to query for callbacks.         * ids (MCallbackIdArray) - Array to store the list of callback IDs.        """        pass


    def removeCallback(self, *args, **kwargs):        """        removeCallback(id) -> None                Removes the specified callback from Maya.        This method must be called for all callbacks registered by a        plug-in before that plug-in is unloaded.                 * id (MCallbackId) - identifier of callback to be removed        """        pass


    def removeCallbacks(self, *args, **kwargs):        """        removeCallbacks(ids) -> None                Removes all of the specified callbacks from Maya.        This method must be called for all callbacks registered by a        plug-in before that plug-in is unloaded.                 * idList (MCallbackIdArray) - list of callbacks to be removed.        """        pass



class MAnimUtil(object):
    """
    Static class providing common animation helper methods.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def isAnimated(self, *args, **kwargs):        """        Return true if the target is animated.        """        pass



class MFnAnimCurve(MFnDependencyNode):
    """
    Function set for operations on anim curves.
    
    __init__()
    Initializes a new, empty MFnAnimCurve object.
    
    __init__(MObject object)
    Initializes a new MFnAnimCurve and attaches it
    to an animCurve object.
    
    __init__(MPlug plug)
    Initializes a new MFnAnimCurve and attaches it
    to the single animCurve node connected to the given MPlug.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def addAttribute(self, *args, **kwargs):        """        Adds a new dynamic attribute to the node.        """        pass


    def addExternalContentForFileAttr(self, *args, **kwargs):        """        Adds content info to the specified table from a file path attribute.        """        pass


    def addKey(self, *args, **kwargs):        """        addKey(at, value, tangentInType=kTangentGlobal, tangentOutType=kTangentGlobal, change=None) -> unsigned int                Adds a new key with the given value at the specified time.        at and value can both be either MTime or double,depending on what is appropriate for the animCurve type.        change is an optional MAnimCurveChange.        """        pass


    def addKeys(self, *args, **kwargs):        """        addKeys(times, values, tangentInType=kTangentGlobal, tangentOutType=kTangentGlobal, keepExistingKeys=False, change=None) -> self                Add a set of new keys with the given corresponding values and tangent typesat the specified times.  This method only works for animCurves of typekAnimCurveTA, kAnimCurveTL and kAnimCurveTU.        """        pass


    def allocateFlag(self, *args, **kwargs):        """        Allocates a flag on all nodes for use by the named plugin and returns the flags index.        """        pass


    @property
    def animCurveType(self, *args, **kwargs):        """        Anim curve type.        """        pass


    def attribute(self, *args, **kwargs):        """        Returns an attribute of the node, given either its index or name.        """        pass


    def attributeClass(self, *args, **kwargs):        """        Returns the class of the specified attribute.        """        pass


    def attributeCount(self, *args, **kwargs):        """        Returns the number of attributes on the node.        """        pass


    def canBeWritten(self, *args, **kwargs):        """        Returns true if the node will be written to file.        """        pass


    def classification(self, *args, **kwargs):        """        Returns the classification string for the named node type.        """        pass


    def create(self, *args, **kwargs):        """        create(node, attribute, animCurveType=kAnimCurveUnknown [, modifier] ) -> MObject        create(plug, animCurveType=kAnimCurveUnknown [, modifier] ) -> MObject        create(animCurveType [, modifier] ) -> MObject                Creates a new animCurve node.        If node and attribute (MObject) are supplied, the animCurvewill be connected to the given attribute on the given node.        If plug (MPlug) is supplied, the animCurvewill be connected to the given plug.        modifier is an optional MDGModifier which can be used to later undo the operation.        animCurveType specifies the type of animCurve to create. Valid values are:        kAnimCurveTA        Time to Angular        kAnimCurveTL        Time to Linear        kAnimCurveTT        Time to Time        kAnimCurveTU        Time to Unitless        kAnimCurveUA        Unitless to Angular        kAnimCurveUL        Unitless to Linear        kAnimCurveUT        Unitless to Time        kAnimCurveUU        Unitless to Unitless        kAnimCurveUnknown    Unknown type        """        pass


    def deallocateAllFlags(self, *args, **kwargs):        """        Deallocates all node flags which are currently allocated to the named plugin.        """        pass


    def deallocateFlag(self, *args, **kwargs):        """        Deallocates the specified node flag, which was previously allocated by the named plugin using allocateFlag().        """        pass


    def dgCallbackIds(self, *args, **kwargs):        """        Returns DG timing information for a specific callback type, broken down by callbackId.        """        pass


    def dgCallbacks(self, *args, **kwargs):        """        Returns DG timing information broken down by callback type.        """        pass


    def dgTimer(self, *args, **kwargs):        """        Returns a specific DG timer metric for a given timer type.        """        pass


    def dgTimerOff(self, *args, **kwargs):        """        Turns DG timing off for this node.        """        pass


    def dgTimerOn(self, *args, **kwargs):        """        Turns DG timing on for this node.        """        pass


    def dgTimerQueryState(self, *args, **kwargs):        """        Returns the current DG timer state for this node.        """        pass


    def dgTimerReset(self, *args, **kwargs):        """        Resets all DG timers for this node.        """        pass


    def evaluate(self, *args, **kwargs):        """        evaluate(at) -> value                Evalutes the curve.        For curves of type kAnimCurveTA, kAnimCurveTL and kAnimCurveTU,the at parameter is an MTime, otherwise it is a double.        For curves of type kAnimCurveTT and kAnimCurveUT,the value is an MTime, otherwise it is a double.                """        pass


    def find(self, *args, **kwargs):        """        find(at) -> unsigned int                Determines the index of the key which is set at the specifiedMTime (time-input curves) or double (unitless-input curves).        Returns None if the key is not found.        """        pass


    def findAlias(self, *args, **kwargs):        """        Returns the attribute which has the given alias.        """        pass


    def findClosest(self, *args, **kwargs):        """        findClosest(at) -> unsigned int                Determines the index of the key which is set at theMTime (time-input curves) or double (unitless-input curves)closest to the specified time.        """        pass


    def findPlug(self, *args, **kwargs):        """        Returns a plug for the given attribute.        """        pass


    def getAffectedAttributes(self, *args, **kwargs):        """        Returns all of the attributes which are affected by the specified attribute.        """        pass


    def getAffectingAttributes(self, *args, **kwargs):        """        Returns all of the attributes which affect the specified attribute.        """        pass


    def getAliasAttr(self, *args, **kwargs):        """        Returns the nodes alias attribute, which is a special attribute used to store information about the nodes attribute aliases.        """        pass


    def getAliasList(self, *args, **kwargs):        """        Returns all of the nodes attribute aliases.        """        pass


    def getConnections(self, *args, **kwargs):        """        Returns all the plugs which are connected to attributes of this node.        """        pass


    def getExternalContent(self, *args, **kwargs):        """        Gets the external content (files) that this node depends on.        """        pass


    def getTangentAngleWeight(self, *args, **kwargs):        """        getTangentAngleWeight(index, isInTangent) -> (MAngle,double)                Determines the angle and weight of the in- or out-tangent to the curvefor the key at the specified index        """        pass


    def getTangentXY(self, *args, **kwargs):        """        getTangentXY(index, isInTangent) -> (x,y)                Determines the x,y value representing the vector of the in- orout-tangent (depending on the value of the isInTangent parameter) tothe curve for the key at the specified index.  The values returnedwill be in Mayas internal units (seconds for time, centimeters forlinear, radians for angles).        """        pass


    def hasAttribute(self, *args, **kwargs):        """        Returns True if the node has an attribute with the given name.        """        pass


    def hasObj(self, *args, **kwargs):        """        Returns True if the function set is compatible with the specified Maya object.        """        pass


    def hasUniqueName(self, *args, **kwargs):        """        Returns True if the nodes name is unique.        """        pass


    def inTangentType(self, *args, **kwargs):        """        inTangentType(index) -> TangentType                Determines the type of the tangent to the curve entering the current key.        """        pass


    def input(self, *args, **kwargs):        """        input(index) -> MTime or double                Determines the input (MTime for T* curves or double for U* curves) of the key at the specified index.        """        pass


    def isBreakdown(self, *args, **kwargs):        """        isBreakdown(index) -> bool                Determines whether or not a key is a breakdown.        """        pass


    @property
    def isDefaultNode(self, *args, **kwargs):        """        True if this is a default node, created automatically by Maya.        """        pass


    def isFlagSet(self, *args, **kwargs):        """        Returns the state of the specified node flag.        """        pass


    @property
    def isFromReferencedFile(self, *args, **kwargs):        """        True if the node is from a referenced file, False if the node is part of the main scene.        """        pass


    @property
    def isLocked(self, *args, **kwargs):        """        True if the node is locked against changes.        """        pass


    def isNewAttribute(self, *args, **kwargs):        """        Returns True if the specified attribute was added in the current scene, and not by by one of its referenced files.        """        pass


    @property
    def isShared(self, *args, **kwargs):        """        True if the node is shared.        """        pass


    @property
    def isStatic(self, *args, **kwargs):        """        Whether the curve is static.        """        pass


    @property
    def isTimeInput(self, *args, **kwargs):        """        Whether the curve has time as an input.        """        pass


    def isTrackingEdits(self, *args, **kwargs):        """        Returns True if the node is referenced or in an assembly that is tracking edits.        """        pass


    @property
    def isUnitlessInput(self, *args, **kwargs):        """        Whether the curve has unitless input.        """        pass


    @property
    def isWeighted(self, *args, **kwargs):        """        Whether the curve has weighted tangents.        """        pass



    kAnimCurveTA = 0


    kAnimCurveTL = 1


    kAnimCurveTT = 2


    kAnimCurveTU = 3


    kAnimCurveUA = 4


    kAnimCurveUL = 5


    kAnimCurveUT = 6


    kAnimCurveUU = 7


    kAnimCurveUnknown = 8


    kConstant = 0


    kCycle = 3


    kCycleRelative = 4


    kExtensionAttr = 3


    kInvalidAttr = 4


    kLinear = 1


    kLocalDynamicAttr = 1


    kNormalAttr = 2


    kOscillate = 5


    kTangentAuto = 11


    kTangentClamped = 8


    kTangentCustomEnd = 32767


    kTangentCustomStart = 64


    kTangentFast = 7


    kTangentFixed = 1


    kTangentFlat = 3


    kTangentGlobal = 0


    kTangentLinear = 2


    kTangentPlateau = 9


    kTangentShared1 = 19


    kTangentShared2 = 20


    kTangentShared3 = 21


    kTangentShared4 = 22


    kTangentShared5 = 23


    kTangentShared6 = 24


    kTangentShared7 = 25


    kTangentShared8 = 26


    kTangentSlow = 6


    kTangentSmooth = 4


    kTangentStep = 5


    kTangentStepNext = 10


    kTangentTypeCount = 32768


    kTimerInvalidState = 3


    kTimerMetric_callback = 0


    kTimerMetric_callbackNotViaAPI = 6


    kTimerMetric_callbackViaAPI = 5


    kTimerMetric_compute = 1


    kTimerMetric_computeDuringCallback = 7


    kTimerMetric_computeNotDuringCallback = 8


    kTimerMetric_dirty = 2


    kTimerMetric_draw = 3


    kTimerMetric_fetch = 4


    kTimerMetrics = 9


    kTimerOff = 0


    kTimerOn = 1


    kTimerType_count = 2


    kTimerType_inclusive = 1


    kTimerType_self = 0


    kTimerTypes = 3


    kTimerUninitialized = 2

    def name(self, *args, **kwargs):        """        Returns the nodes name.        """        pass


    @property
    def namespace(self, *args, **kwargs):        """        Name of the namespace which contains the node.        """        pass


    @property
    def numKeys(self, *args, **kwargs):        """        Number of keys.        """        pass


    def object(self, *args, **kwargs):        """        Returns a reference to the object to which the function set is currently attached, or MObject.kNullObj if none.        """        pass


    def outTangentType(self, *args, **kwargs):        """        outTangentType(index) -> TangentType                Determines the type of the tangent to the curve leaving the current key.        """        pass


    @property
    def pluginName(self, *args, **kwargs):        """        Name of the plugin which registered the node type, if any.        """        pass


    def plugsAlias(self, *args, **kwargs):        """        Returns the alias for a plugs attribute.        """        pass


    @property
    def postInfinityType(self, *args, **kwargs):        """        The curves post-infinity type.        """        pass


    @property
    def preInfinityType(self, *args, **kwargs):        """        The curves pre-infinity type.        """        pass


    def remove(self, *args, **kwargs):        """        remove(index, change=None) -> self                Removes the key at the specified index.        change is an optional MAnimCurveChange.        """        pass


    def removeAttribute(self, *args, **kwargs):        """        Removes a dynamic attribute from the node.        """        pass


    def reorderedAttribute(self, *args, **kwargs):        """        Returns one of the nodes attribute, based on the order in which they are written to file.        """        pass


    def setAlias(self, *args, **kwargs):        """        Adds or removes an attribute alias.        """        pass


    def setAngle(self, *args, **kwargs):        """        setAngle(index, setAngle, isInTangent, change=None) -> self                Sets the in- or out-angle of the tangent for the key at the given index.        isInTangent is True to modify the inTangent or False to modify the outTangent.        """        pass


    def setDoNotWrite(self, *args, **kwargs):        """        Used to prevent the node from being written to file.        """        pass


    def setExternalContent(self, *args, **kwargs):        """        Changes the location of external content.        """        pass


    def setExternalContentForFileAttr(self, *args, **kwargs):        """        Sets content info in the specified attribute from the table.        """        pass


    def setFlag(self, *args, **kwargs):        """        Sets the state of the specified node flag.        """        pass


    def setInTangentType(self, *args, **kwargs):        """        setInTangentType(index, tangentType, change=None) -> self                Sets the type of the tangent to the curve entering the key at thespecified index.        Valid values for tangentType are:        kTangentGlobal        Global        kTangentFixed        Fixed        kTangentLinear        Linear        kTangentFlat        Flag        kTangentSmooth        Smooth        kTangentStep        Step        kTangentSlow        OBSOLETE kTangentSlow should not be used. Using this tangent type may produce unwanted and unexpected results.        kTangentFast        OBSOLETE kTangentFast should not be used. Using this tangent type may produce unwanted and unexpected results.        kTangentClamped    Clamped        kTangentPlateau    Plateau        kTangentStepNext    StepNext        kTangentAuto        Auto        """        pass


    def setInput(self, *args, **kwargs):        """        setInput(index, at, change=None) -> self                Sets the input (MTime for T* curves or double for U* curves) of the key at the specified index.  This will fail ifsetting the input would require re-ordering of the keys.        """        pass


    def setIsBreakdown(self, *args, **kwargs):        """        setIsBreakdown(index, isBreakdown, change=None) -> self                Sets the breakdown state of a key at a given index.        """        pass


    def setIsWeighted(self, *args, **kwargs):        """        setIsWeighted(isWeighted, change=None) -> self                Sets whether or not the curve has weighted tangents.        """        pass


    def setName(self, *args, **kwargs):        """        Sets the nodes name.        """        pass


    def setObject(self, *args, **kwargs):        """        Attaches the function set to the specified Maya object.        """        pass


    def setOutTangentType(self, *args, **kwargs):        """        setOutTangentType(index, tangentType, change=None) -> self                Sets the type of the tangent to the curve leaving the key at thespecified index.        """        pass


    def setPostInfinityType(self, *args, **kwargs):        """        setPostInfinityType(infinityType, change=None) -> self                Sets the behaviour of the curve for the range occurring after the last key.        """        pass


    def setPreInfinityType(self, *args, **kwargs):        """        setPreInfinityType(infinityType, change=None) -> self                Sets the behaviour of the curve for the range occurring before the first key.        Valid values for infinityType are:        kConstant            Constant        kLinear            Linear        kCycle                Cycle        kCycleRelative        Cycle relative        kOscillate            Oscillate        """        pass


    def setTangent(self, *args, **kwargs):        """        setTangent(index, xOrAngle, yOrWeight, isInTangent, change=None, convertUnits=True) -> self                Sets the tangent for the key at the specified index.        The tangent can be specified as an x/y pair, oras an MAngle and a weight.        isInTangent is True to modify the inTangent or False to modify the outTangent.        """        pass


    def setTangentTypes(self, *args, **kwargs):        """        setTangentTypes(indexArray, tangentInType=kTangentGlobal, tangentOutType=kTangentGlobal, change=None) -> self                Sets the tangent types for multiple keys.        """        pass


    def setTangentsLocked(self, *args, **kwargs):        """        setTangentsLocked(index, locked, change=None) -> self                Lock or unlock the tangents at the given key.        """        pass


    def setUuid(self, *args, **kwargs):        """        Sets the nodes UUID.        """        pass


    def setValue(self, *args, **kwargs):        """        setValue(index, value, change=None) -> self                Sets the value of the key at the specified index.  This methodshould only be used on Anim Curves of type kAnimCurve*A, kAnimCurve*Lor kAnimCurve*U.        """        pass


    def setWeight(self, *args, **kwargs):        """        setWeight(index, weight, isInTangent, change=None) -> self                Sets the in- or out-weight of the tangent for the key at the given index.        isInTangent is True to modify the inTangent or False to modify the outTangent.        """        pass


    def setWeightsLocked(self, *args, **kwargs):        """        setWeightsLocked(index, locked, change=None) -> self                Lock or unlock the weights at the given key.        """        pass


    def tangentsLocked(self, *args, **kwargs):        """        tangentsLocked(index) -> bool                Determines whether the tangents are locked at the given key.        """        pass


    def timedAnimCurveTypeForPlug(self, *args, **kwargs):        """        timedAnimCurveTypeForPlug(plug) -> AnimCurveType                Returns the timed animCurve type appropriate for the specified plug.        """        pass


    def type(self, *args, **kwargs):        """        Returns the type of the function set.        """        pass


    @property
    def typeId(self, *args, **kwargs):        """        MTypeId for the nodes type.        """        pass


    @property
    def typeName(self, *args, **kwargs):        """        Name of the nodes type.        """        pass


    def unitlessAnimCurveTypeForPlug(self, *args, **kwargs):        """        unitlessAnimCurveTypeForPlug(plug) -> AnimCurveType                Returns the unitless animCurve type appropriate for the specified plug.        """        pass


    def userNode(self, *args, **kwargs):        """        Returns the MPxNode object for a plugin node.        """        pass


    def uuid(self, *args, **kwargs):        """        Returns the nodes UUID.        """        pass


    def value(self, *args, **kwargs):        """        value(index) -> double                Determines the value of the key at the specified index.  This methodshould only be used on Anim Curves of type kAnimCurve*A, kAnimCurve*Lor kAnimCurve*U.        """        pass


    def weightsLocked(self, *args, **kwargs):        """        weightsLocked(index) -> bool                Determines whether the weights are locked at the given key.        """        pass



class MFnGeometryFilter(MFnDependencyNode):
    """
    Function set for operating on geometryFilter nodes.
    geometryFilter is the abstract node type from which all
    deformer node types derive.
    
    __init__()
    Initializes a new, empty MFnGeometryFilter functionset.
    
    __init__(MObject)
    Initializes a new MFnGeometryFilter functionset and attaches it
    to a geometryFilter node.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def addAttribute(self, *args, **kwargs):        """        Adds a new dynamic attribute to the node.        """        pass


    def addExternalContentForFileAttr(self, *args, **kwargs):        """        Adds content info to the specified table from a file path attribute.        """        pass


    def allocateFlag(self, *args, **kwargs):        """        Allocates a flag on all nodes for use by the named plugin and returns the flags index.        """        pass


    def attribute(self, *args, **kwargs):        """        Returns an attribute of the node, given either its index or name.        """        pass


    def attributeClass(self, *args, **kwargs):        """        Returns the class of the specified attribute.        """        pass


    def attributeCount(self, *args, **kwargs):        """        Returns the number of attributes on the node.        """        pass


    def canBeWritten(self, *args, **kwargs):        """        Returns true if the node will be written to file.        """        pass


    def classification(self, *args, **kwargs):        """        Returns the classification string for the named node type.        """        pass


    def create(self, *args, **kwargs):        """        Creates a new node of the given type.        """        pass


    def deallocateAllFlags(self, *args, **kwargs):        """        Deallocates all node flags which are currently allocated to the named plugin.        """        pass


    def deallocateFlag(self, *args, **kwargs):        """        Deallocates the specified node flag, which was previously allocated by the named plugin using allocateFlag().        """        pass


    @property
    def deformerSet(self, *args, **kwargs):        """        Object set containing the objects that are deformed. Adding new        components to the deformer set will cause them to be deformed.        Removing components from the deformer set will prevent them from        being influenced by the deformer.                Note that the wrap deformer and the skinCluster deformers are        special cases: they allow only a single object to be deformed per        wrap/skinCluster, so adding additional geometries to them will have        no effect.        """        pass


    def dgCallbackIds(self, *args, **kwargs):        """        Returns DG timing information for a specific callback type, broken down by callbackId.        """        pass


    def dgCallbacks(self, *args, **kwargs):        """        Returns DG timing information broken down by callback type.        """        pass


    def dgTimer(self, *args, **kwargs):        """        Returns a specific DG timer metric for a given timer type.        """        pass


    def dgTimerOff(self, *args, **kwargs):        """        Turns DG timing off for this node.        """        pass


    def dgTimerOn(self, *args, **kwargs):        """        Turns DG timing on for this node.        """        pass


    def dgTimerQueryState(self, *args, **kwargs):        """        Returns the current DG timer state for this node.        """        pass


    def dgTimerReset(self, *args, **kwargs):        """        Resets all DG timers for this node.        """        pass


    @property
    def envelope(self, *args, **kwargs):        """        A global scale factor that is applied to all the values.        """        pass


    def findAlias(self, *args, **kwargs):        """        Returns the attribute which has the given alias.        """        pass


    def findPlug(self, *args, **kwargs):        """        Returns a plug for the given attribute.        """        pass


    def getAffectedAttributes(self, *args, **kwargs):        """        Returns all of the attributes which are affected by the specified attribute.        """        pass


    def getAffectingAttributes(self, *args, **kwargs):        """        Returns all of the attributes which affect the specified attribute.        """        pass


    def getAliasAttr(self, *args, **kwargs):        """        Returns the nodes alias attribute, which is a special attribute used to store information about the nodes attribute aliases.        """        pass


    def getAliasList(self, *args, **kwargs):        """        Returns all of the nodes attribute aliases.        """        pass


    def getConnections(self, *args, **kwargs):        """        Returns all the plugs which are connected to attributes of this node.        """        pass


    def getExternalContent(self, *args, **kwargs):        """        Gets the external content (files) that this node depends on.        """        pass


    def getInputGeometry(self, *args, **kwargs):        """        getInputGeometry() -> MObjectArray                Returns the DAG nodes which provide input geometry to the deformer.        These are found by traversing the graph to find upstream shape nodes.        It is possible for there to be nodes in between the shape and the        deformer so that the returned shape may have a different topology or        tweaks then the input data to the deformer. If the actual input        geometry data for the deformer is required, this information can be        accessed by using MPlug::getValue() to query the inputGeometry        attribute on the deformer.        """        pass


    def getOutputGeometry(self, *args, **kwargs):        """        getOutputGeometry() -> MObjectArray                Returns the DAG nodes which receive output geometry from the deformer.        """        pass


    def getPathAtIndex(self, *args, **kwargs):        """        getPathAtIndex(plugIndex) -> MDagPath                Returns the DAG path of the specified output geometry.                * plugIndex (unsigned int) - Plug index of the desired geometry.        """        pass


    def groupIdAtIndex(self, *args, **kwargs):        """        groupIdAtIndex(plugIndex) -> long                Returns the groupId associated with the specified geometry.                * plugIndex (unsigned int) - Plug index of the desired geometry.        """        pass


    def hasAttribute(self, *args, **kwargs):        """        Returns True if the node has an attribute with the given name.        """        pass


    def hasObj(self, *args, **kwargs):        """        Returns True if the function set is compatible with the specified Maya object.        """        pass


    def hasUniqueName(self, *args, **kwargs):        """        Returns True if the nodes name is unique.        """        pass


    def indexForGroupId(self, *args, **kwargs):        """        indexForGroupId(groupId) -> plugIndex                Returns the plug index of the geometry associated with the specified groupId.                * groupId (unsigned int) - groupId of the desired geometry.        """        pass


    def indexForOutputConnection(self, *args, **kwargs):        """        indexForOutputConnection(connIndex) -> plugIndex                Returns the plug index corresponding to a connection index. The        connection index is the contiguous (physical) index of the output        connection, ranging from 0 to numOutputConnections()-1. The plug        index is the sparse (logical) index of the connection.                * connIndex (unsigned int) - Connection index of the desired geometry.        """        pass


    def indexForOutputShape(self, *args, **kwargs):        """        indexForOutputShape(shape) -> plugIndex                Returns the plug index for the specified output shape.                * shape (MObject) - Shape for which the plug index is requested.        """        pass


    def inputShapeAtIndex(self, *args, **kwargs):        """        inputShapeAtIndex(plugIndex) -> MObject                Returns the input shape corresponding to the plug index.                * plugIndex (unsigned int) - Plug index of the desired shape.        """        pass


    @property
    def isDefaultNode(self, *args, **kwargs):        """        True if this is a default node, created automatically by Maya.        """        pass


    def isFlagSet(self, *args, **kwargs):        """        Returns the state of the specified node flag.        """        pass


    @property
    def isFromReferencedFile(self, *args, **kwargs):        """        True if the node is from a referenced file, False if the node is part of the main scene.        """        pass


    @property
    def isLocked(self, *args, **kwargs):        """        True if the node is locked against changes.        """        pass


    def isNewAttribute(self, *args, **kwargs):        """        Returns True if the specified attribute was added in the current scene, and not by by one of its referenced files.        """        pass


    @property
    def isShared(self, *args, **kwargs):        """        True if the node is shared.        """        pass


    def isTrackingEdits(self, *args, **kwargs):        """        Returns True if the node is referenced or in an assembly that is tracking edits.        """        pass



    kExtensionAttr = 3


    kInvalidAttr = 4


    kLocalDynamicAttr = 1


    kNormalAttr = 2


    kTimerInvalidState = 3


    kTimerMetric_callback = 0


    kTimerMetric_callbackNotViaAPI = 6


    kTimerMetric_callbackViaAPI = 5


    kTimerMetric_compute = 1


    kTimerMetric_computeDuringCallback = 7


    kTimerMetric_computeNotDuringCallback = 8


    kTimerMetric_dirty = 2


    kTimerMetric_draw = 3


    kTimerMetric_fetch = 4


    kTimerMetrics = 9


    kTimerOff = 0


    kTimerOn = 1


    kTimerType_count = 2


    kTimerType_inclusive = 1


    kTimerType_self = 0


    kTimerTypes = 3


    kTimerUninitialized = 2

    def name(self, *args, **kwargs):        """        Returns the nodes name.        """        pass


    @property
    def namespace(self, *args, **kwargs):        """        Name of the namespace which contains the node.        """        pass


    def numOutputConnections(self, *args, **kwargs):        """        numOutputConnections() -> long                Returns the number of output geometries connected to this node. This        is typically equal to the number of input geometries unless an input        or output geometry has been deleted, or a connection to an input or        output geometry has been broken.                This method is useful in conjunction with indexForOutputConnection()        to iterate through the affected objects.        """        pass


    def object(self, *args, **kwargs):        """        Returns a reference to the object to which the function set is currently attached, or MObject.kNullObj if none.        """        pass


    def outputShapeAtIndex(self, *args, **kwargs):        """        outputShapeAtIndex(index) -> MObject                Returns the DAG path to which this function set is attached, or the first path to the node if the function set is attached to an MObject.        """        pass


    @property
    def pluginName(self, *args, **kwargs):        """        Name of the plugin which registered the node type, if any.        """        pass


    def plugsAlias(self, *args, **kwargs):        """        Returns the alias for a plugs attribute.        """        pass


    def removeAttribute(self, *args, **kwargs):        """        Removes a dynamic attribute from the node.        """        pass


    def reorderedAttribute(self, *args, **kwargs):        """        Returns one of the nodes attribute, based on the order in which they are written to file.        """        pass


    def setAlias(self, *args, **kwargs):        """        Adds or removes an attribute alias.        """        pass


    def setDoNotWrite(self, *args, **kwargs):        """        Used to prevent the node from being written to file.        """        pass


    def setExternalContent(self, *args, **kwargs):        """        Changes the location of external content.        """        pass


    def setExternalContentForFileAttr(self, *args, **kwargs):        """        Sets content info in the specified attribute from the table.        """        pass


    def setFlag(self, *args, **kwargs):        """        Sets the state of the specified node flag.        """        pass


    def setName(self, *args, **kwargs):        """        Sets the nodes name.        """        pass


    def setObject(self, *args, **kwargs):        """        Attaches the function set to the specified Maya object.        """        pass


    def setUuid(self, *args, **kwargs):        """        Sets the nodes UUID.        """        pass


    def type(self, *args, **kwargs):        """        Returns the type of the function set.        """        pass


    @property
    def typeId(self, *args, **kwargs):        """        MTypeId for the nodes type.        """        pass


    @property
    def typeName(self, *args, **kwargs):        """        Name of the nodes type.        """        pass


    def userNode(self, *args, **kwargs):        """        Returns the MPxNode object for a plugin node.        """        pass


    def uuid(self, *args, **kwargs):        """        Returns the nodes UUID.        """        pass



class MFnSkinCluster(MFnGeometryFilter):
    """
    Function set for operating on skinCluster nodes.
    SkinCluster nodes are created during a smooth bindSkin. They
    store a weight per influence object for each component of the
    geometry that is deformed. Influence objects can be joints or
    any transform.
    
    Unlike most deformers, a skinCluster node can deform only a
    single geometry. Therefore, if additional geometries are added
    to the skinCluster set, they will be ignored.
    
    __init__()
    Initializes a new, empty MFnSkinCluster functionset.
    
    __init__(MObject)
    Initializes a new MFnSkinCluster functionset and attaches it to
    a skinCluster node.
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def addAttribute(self, *args, **kwargs):        """        Adds a new dynamic attribute to the node.        """        pass


    def addExternalContentForFileAttr(self, *args, **kwargs):        """        Adds content info to the specified table from a file path attribute.        """        pass


    def allocateFlag(self, *args, **kwargs):        """        Allocates a flag on all nodes for use by the named plugin and returns the flags index.        """        pass


    def attribute(self, *args, **kwargs):        """        Returns an attribute of the node, given either its index or name.        """        pass


    def attributeClass(self, *args, **kwargs):        """        Returns the class of the specified attribute.        """        pass


    def attributeCount(self, *args, **kwargs):        """        Returns the number of attributes on the node.        """        pass


    def canBeWritten(self, *args, **kwargs):        """        Returns true if the node will be written to file.        """        pass


    def classification(self, *args, **kwargs):        """        Returns the classification string for the named node type.        """        pass


    def create(self, *args, **kwargs):        """        Creates a new node of the given type.        """        pass


    def deallocateAllFlags(self, *args, **kwargs):        """        Deallocates all node flags which are currently allocated to the named plugin.        """        pass


    def deallocateFlag(self, *args, **kwargs):        """        Deallocates the specified node flag, which was previously allocated by the named plugin using allocateFlag().        """        pass


    @property
    def deformerSet(self, *args, **kwargs):        """        Object set containing the objects that are deformed. Adding new        components to the deformer set will cause them to be deformed.        Removing components from the deformer set will prevent them from        being influenced by the deformer.                Note that the wrap deformer and the skinCluster deformers are        special cases: they allow only a single object to be deformed per        wrap/skinCluster, so adding additional geometries to them will have        no effect.        """        pass


    def dgCallbackIds(self, *args, **kwargs):        """        Returns DG timing information for a specific callback type, broken down by callbackId.        """        pass


    def dgCallbacks(self, *args, **kwargs):        """        Returns DG timing information broken down by callback type.        """        pass


    def dgTimer(self, *args, **kwargs):        """        Returns a specific DG timer metric for a given timer type.        """        pass


    def dgTimerOff(self, *args, **kwargs):        """        Turns DG timing off for this node.        """        pass


    def dgTimerOn(self, *args, **kwargs):        """        Turns DG timing on for this node.        """        pass


    def dgTimerQueryState(self, *args, **kwargs):        """        Returns the current DG timer state for this node.        """        pass


    def dgTimerReset(self, *args, **kwargs):        """        Resets all DG timers for this node.        """        pass


    @property
    def envelope(self, *args, **kwargs):        """        A global scale factor that is applied to all the values.        """        pass


    def findAlias(self, *args, **kwargs):        """        Returns the attribute which has the given alias.        """        pass


    def findPlug(self, *args, **kwargs):        """        Returns a plug for the given attribute.        """        pass


    def getAffectedAttributes(self, *args, **kwargs):        """        Returns all of the attributes which are affected by the specified attribute.        """        pass


    def getAffectingAttributes(self, *args, **kwargs):        """        Returns all of the attributes which affect the specified attribute.        """        pass


    def getAliasAttr(self, *args, **kwargs):        """        Returns the nodes alias attribute, which is a special attribute used to store information about the nodes attribute aliases.        """        pass


    def getAliasList(self, *args, **kwargs):        """        Returns all of the nodes attribute aliases.        """        pass


    def getBlendWeights(self, *args, **kwargs):        """        getBlendWeights(shape, components) -> MDoubleArray                Returns blend weights for the specified components of the deformed        shape. Blend weights are used to determine the blending between        classical linear skinning and dual quaternion bases skinning on a        per vertex basis. The returned array contains one weight per component        in the order given by components.                * shape     (MDagPath) - the object being deformed by the skinCluster        * components (MObject) - components for which weights should be returned        """        pass


    def getConnections(self, *args, **kwargs):        """        Returns all the plugs which are connected to attributes of this node.        """        pass


    def getExternalContent(self, *args, **kwargs):        """        Gets the external content (files) that this node depends on.        """        pass


    def getInputGeometry(self, *args, **kwargs):        """        getInputGeometry() -> MObjectArray                Returns the DAG nodes which provide input geometry to the deformer.        These are found by traversing the graph to find upstream shape nodes.        It is possible for there to be nodes in between the shape and the        deformer so that the returned shape may have a different topology or        tweaks then the input data to the deformer. If the actual input        geometry data for the deformer is required, this information can be        accessed by using MPlug::getValue() to query the inputGeometry        attribute on the deformer.        """        pass


    def getOutputGeometry(self, *args, **kwargs):        """        getOutputGeometry() -> MObjectArray                Returns the DAG nodes which receive output geometry from the deformer.        """        pass


    def getPathAtIndex(self, *args, **kwargs):        """        getPathAtIndex(plugIndex) -> MDagPath                Returns the DAG path of the specified output geometry.                * plugIndex (unsigned int) - Plug index of the desired geometry.        """        pass


    def getPointsAffectedByInfluence(self, *args, **kwargs):        """        getPointsAffectedByInfluence(influence) -> (MSelectionList, MDoubleArray)                During deformation, the skinCluster algorithm is applied for a given        influence object on all points in the deformers set whose weights        are non-zero. This returns the non-zero weights for a particular        influence object.                The return value is a tuple consisting of a selection list, which        contains the dag path and components that are affected by the        specified influence object, and the corresponding weights for the        components. If no components are weighted for a specified influence        the selection list will be empty.                * influence (MDagPath) - the influence object of interest        """        pass


    def getWeights(self, *args, **kwargs):        """        getWeights(shape, components) -> (MDoubleArray, int)        getWeights(shape, components, influence) -> MDoubleArray        getWeights(shape, components, influences) -> MDoubleArray                Returns the skinCluster weights of the given influence objects on        the specified components of the deformed shape.                        If no influence index is provided then a tuple containing the weights        and the number of influence objects will be returned.                If a single influence index is provided the an array of weights will        be returned, one per component in the same order as in components.                If an array of influence indices is provided an array of weights will        be returned containing as many weights for each component as there        are influences in the influenceIndices array. The weights will be        in component order: i.e. all of the weight values for the first        component, followed by all the weight values for the second component,        and so on.                * shape       (MDagPath) - the object being deformed by the skinCluster        * components   (MObject) - components to return weights for        * influence        (int) - index of the single influence to return weights for        * influences (MIntArray) - indices of multiple influences to return weights for        """        pass


    def groupIdAtIndex(self, *args, **kwargs):        """        groupIdAtIndex(plugIndex) -> long                Returns the groupId associated with the specified geometry.                * plugIndex (unsigned int) - Plug index of the desired geometry.        """        pass


    def hasAttribute(self, *args, **kwargs):        """        Returns True if the node has an attribute with the given name.        """        pass


    def hasObj(self, *args, **kwargs):        """        Returns True if the function set is compatible with the specified Maya object.        """        pass


    def hasUniqueName(self, *args, **kwargs):        """        Returns True if the nodes name is unique.        """        pass


    def indexForGroupId(self, *args, **kwargs):        """        indexForGroupId(groupId) -> plugIndex                Returns the plug index of the geometry associated with the specified groupId.                * groupId (unsigned int) - groupId of the desired geometry.        """        pass


    def indexForInfluenceObject(self, *args, **kwargs):        """        indexForInfluenceObject(influenceObj) -> long                Returns the logical index of the matrix array attribute where the        specified influence object is attached.                * influenceObj (MObject) - influence object for which the index is requested.        """        pass


    def indexForOutputConnection(self, *args, **kwargs):        """        indexForOutputConnection(connIndex) -> plugIndex                Returns the plug index corresponding to a connection index. The        connection index is the contiguous (physical) index of the output        connection, ranging from 0 to numOutputConnections()-1. The plug        index is the sparse (logical) index of the connection.                * connIndex (unsigned int) - Connection index of the desired geometry.        """        pass


    def indexForOutputShape(self, *args, **kwargs):        """        indexForOutputShape(shape) -> plugIndex                Returns the plug index for the specified output shape.                * shape (MObject) - Shape for which the plug index is requested.        """        pass


    def influenceObjects(self, *args, **kwargs):        """        influenceObjects() -> MDagPathArray                Returns an array of paths to the influence objects for the skinCluster.        """        pass


    def inputShapeAtIndex(self, *args, **kwargs):        """        inputShapeAtIndex(plugIndex) -> MObject                Returns the input shape corresponding to the plug index.                * plugIndex (unsigned int) - Plug index of the desired shape.        """        pass


    @property
    def isDefaultNode(self, *args, **kwargs):        """        True if this is a default node, created automatically by Maya.        """        pass


    def isFlagSet(self, *args, **kwargs):        """        Returns the state of the specified node flag.        """        pass


    @property
    def isFromReferencedFile(self, *args, **kwargs):        """        True if the node is from a referenced file, False if the node is part of the main scene.        """        pass


    @property
    def isLocked(self, *args, **kwargs):        """        True if the node is locked against changes.        """        pass


    def isNewAttribute(self, *args, **kwargs):        """        Returns True if the specified attribute was added in the current scene, and not by by one of its referenced files.        """        pass


    @property
    def isShared(self, *args, **kwargs):        """        True if the node is shared.        """        pass


    def isTrackingEdits(self, *args, **kwargs):        """        Returns True if the node is referenced or in an assembly that is tracking edits.        """        pass



    kExtensionAttr = 3


    kInvalidAttr = 4


    kLocalDynamicAttr = 1


    kNormalAttr = 2


    kTimerInvalidState = 3


    kTimerMetric_callback = 0


    kTimerMetric_callbackNotViaAPI = 6


    kTimerMetric_callbackViaAPI = 5


    kTimerMetric_compute = 1


    kTimerMetric_computeDuringCallback = 7


    kTimerMetric_computeNotDuringCallback = 8


    kTimerMetric_dirty = 2


    kTimerMetric_draw = 3


    kTimerMetric_fetch = 4


    kTimerMetrics = 9


    kTimerOff = 0


    kTimerOn = 1


    kTimerType_count = 2


    kTimerType_inclusive = 1


    kTimerType_self = 0


    kTimerTypes = 3


    kTimerUninitialized = 2

    def name(self, *args, **kwargs):        """        Returns the nodes name.        """        pass


    @property
    def namespace(self, *args, **kwargs):        """        Name of the namespace which contains the node.        """        pass


    def numOutputConnections(self, *args, **kwargs):        """        numOutputConnections() -> long                Returns the number of output geometries connected to this node. This        is typically equal to the number of input geometries unless an input        or output geometry has been deleted, or a connection to an input or        output geometry has been broken.                This method is useful in conjunction with indexForOutputConnection()        to iterate through the affected objects.        """        pass


    def object(self, *args, **kwargs):        """        Returns a reference to the object to which the function set is currently attached, or MObject.kNullObj if none.        """        pass


    def outputShapeAtIndex(self, *args, **kwargs):        """        outputShapeAtIndex(index) -> MObject                Returns the DAG path to which this function set is attached, or the first path to the node if the function set is attached to an MObject.        """        pass


    @property
    def pluginName(self, *args, **kwargs):        """        Name of the plugin which registered the node type, if any.        """        pass


    def plugsAlias(self, *args, **kwargs):        """        Returns the alias for a plugs attribute.        """        pass


    def removeAttribute(self, *args, **kwargs):        """        Removes a dynamic attribute from the node.        """        pass


    def reorderedAttribute(self, *args, **kwargs):        """        Returns one of the nodes attribute, based on the order in which they are written to file.        """        pass


    def setAlias(self, *args, **kwargs):        """        Adds or removes an attribute alias.        """        pass


    def setBlendWeights(self, *args, **kwargs):        """        setBlendWeights(shape, components, weights) -> self                Sets blend weights for the specified components of the shape being        deformed by the skinCluster. Blend weights are used to determine the        blending between classical linear skinning and dual quaternion bases        skinning on a per vertex basis.                * shape       (MDagPath) - object being deformed by the skinCluster        * components   (MObject) - components of shape to set blend weights for        * weights (MDoubleArray) - weights to set, one per component. If the                                   length of this array does match the number                                   of components provided then the lesser of                                   the two will be used.        """        pass


    def setDoNotWrite(self, *args, **kwargs):        """        Used to prevent the node from being written to file.        """        pass


    def setExternalContent(self, *args, **kwargs):        """        Changes the location of external content.        """        pass


    def setExternalContentForFileAttr(self, *args, **kwargs):        """        Sets content info in the specified attribute from the table.        """        pass


    def setFlag(self, *args, **kwargs):        """        Sets the state of the specified node flag.        """        pass


    def setName(self, *args, **kwargs):        """        Sets the nodes name.        """        pass


    def setObject(self, *args, **kwargs):        """        Attaches the function set to the specified Maya object.        """        pass


    def setUuid(self, *args, **kwargs):        """        Sets the nodes UUID.        """        pass


    def setWeights(self, *args, **kwargs):        """        setWeights(shape, components, influence, weight, normalize=True, returnOldWeights=False) -> None or MDoubleArray        setWeights(shape, components, influences, weights, normalize=True, returnOldWeights=False) -> None or MDoubleArray                Sets the skinCluster weights for one or more influence objects on        the specified components of the given shape. If returnOldWeights        is True then the old weights will be returned, otherwise None will        be returned                If only a single influence index and weight are specified then that        weight is applied to all of the specified components. The returned        array of old weights, if requested, will contain weights for ALL of        the skinClusters influence objects, not just the one specified by        the influence parameter.                If arrays of influence indices and weights are provided then the        behaviour depends upon the number of elements in the weights array.        If its equal to the number of influences specified then each weight        will be used for all of components for the corresponding influence        object. If its equal to the number of influences times the number of        components provided, then a separate weight will be used for each        component, with all of the weights for the first component coming        first in the weights array, followed by all of the weights for the        second component, and so on. Within each component the weights will        will correspond with the ordering of influence indices in the        influences array. The returned old weights, if requested, will        consist of a separate weight for                The returned old weights will be ordered by influence within        component, i.e. all of the influence weights for the first component        will come first in the array, followed by all the weights for the        second component, and so on.                * shape       (MDagPath) - object being deformed by the skinCluster        * components   (MObject) - the components to set weights on        * influence        (int) - physical index of a single influence object        * weight         (float) - single weight to be applied to all components.        * influences (MIntArray) - physical indices of several influence objects.        * weights (MDoubleArray) - weights to be used with several influence objects.        * normalize       (bool) - if True, normalize weights on other influence objects        * returnOldWeights(bool) - if True, return the old weights, otherwise return None        """        pass


    def type(self, *args, **kwargs):        """        Returns the type of the function set.        """        pass


    @property
    def typeId(self, *args, **kwargs):        """        MTypeId for the nodes type.        """        pass


    @property
    def typeName(self, *args, **kwargs):        """        Name of the nodes type.        """        pass


    def userNode(self, *args, **kwargs):        """        Returns the MPxNode object for a plugin node.        """        pass


    def uuid(self, *args, **kwargs):        """        Returns the nodes UUID.        """        pass



class val(object):
    """
    Control over animation playback and values
    """

    def __init__(self, *args, **kwargs):        """        x.__init__(...) initializes x; see help(type(x)) for signature        """        pass


    def __repr__(self, *args, **kwargs):        """        x.__repr__() <==> repr(x)        """        pass


    def __str__(self, *args, **kwargs):        """        x.__str__() <==> str(x)        """        pass


    def animationEndTime(self, *args, **kwargs):        """        animationEndTime() -> MTime                Return an MTime specifying the last frame of the animation, as specified by the Maya user in the Range Slider UI.        """        pass


    def animationStartTime(self, *args, **kwargs):        """        animationStartTime() -> MTime                Return an MTime specifying the first frame of the animation, as specified by the Maya user in the Range Slider UI.        """        pass


    def autoKeyMode(self, *args, **kwargs):        """        autoKeyMode() -> bool                Return the autoKeyMode.        """        pass


    def currentTime(self, *args, **kwargs):        """        currentTime() -> MTime                Return an MTime instance containing the current animation frame.        """        pass


    def globalInTangentType(self, *args, **kwargs):        """        globalInTangentType() -> int                Return the current global in tangent type.        """        pass


    def globalOutTangentType(self, *args, **kwargs):        """        globalOutTangentType() -> int                Return the current global out tangent type.        """        pass


    def isPlaying(self, *args, **kwargs):        """        isPlaying() -> bool                Return a value indicating whether Maya is currently playing the animation        """        pass


    def isScrubbing(self, *args, **kwargs):        """        isScrubbing() -> bool                Return a value indicating whether interactive scrubbing is occuring while Maya is not currently playing an animation.        """        pass



    kPlaybackLoop = 1


    kPlaybackOnce = 0


    kPlaybackOscillate = 2


    kPlaybackViewActive = 1


    kPlaybackViewAll = 0

    def maxTime(self, *args, **kwargs):        """        maxTime() -> MTime                Return an MTime specifying the last frame of the current playback time range.        """        pass


    def minTime(self, *args, **kwargs):        """        minTime() -> MTime                Return an MTime specifying the first frame of the current playback time range.        """        pass


    def playBackward(self, *args, **kwargs):        """        playBackward() -> None                Start playing the current animation backwards.        """        pass


    def playForward(self, *args, **kwargs):        """        playForward() -> None                Start playing the current animation forwards.        """        pass


    def playbackBy(self, *args, **kwargs):        """        playbackBy() -> float                Return a float specifying the increment between times viewed during the playing of the animation.        """        pass


    def playbackMode(self, *args, **kwargs):        """        playbackMode() -> int                Return the playback mode currently in effect:          MAnimControl.kPlaybackOnce         Play once then stop.          MAnimControl.kPlaybackLoop         Play continuously.          MAnimControl.kPlaybackOscillate    Play forwards, then backwards continuously.        """        pass


    def playbackSpeed(self, *args, **kwargs):        """        playbackSpeed() -> float                Return the speed with with to play the animation.        """        pass


    def setAnimationEndTime(self, *args, **kwargs):        """        setAnimationEndTime(MTime) -> None                Set the value of the last frame in the animation.        """        pass


    def setAnimationStartEndTime(self, *args, **kwargs):        """        setAnimationStartEndTime(MTime, MTime) -> None                Set the values of the first and last frames in the animation.        """        pass


    def setAnimationStartTime(self, *args, **kwargs):        """        setAnimationStartTime(MTime) -> None                Set the value of the first frame in the animation.        """        pass


    def setAutoKeyMode(self, *args, **kwargs):        """        setAutoKeyMode(bool) -> None                Set the autoKeyMode.        """        pass


    def setCurrentTime(self, *args, **kwargs):        """        setMinTime(MTime) -> None                Set the current animation frame.        """        pass


    def setGlobalInTangentType(self, *args, **kwargs):        """        setGlobalInTangentType(int) -> None                Set the current global in tangent type        """        pass


    def setGlobalOutTangentType(self, *args, **kwargs):        """        setGlobalOutTangentType(int) -> None                Set the current global out tangent type.        """        pass


    def setMaxTime(self, *args, **kwargs):        """        setMaxTime(MTime) -> None                Set the value of the last frame of the current playback time range.        """        pass


    def setMinMaxTime(self, *args, **kwargs):        """        setMinMaxTime(MTime, MTime) -> None                Set the values of the first and last frames of the playback time range.        """        pass


    def setMinTime(self, *args, **kwargs):        """        setMinTime(MTime) -> None                Set the value of the first frame of the current playback time range.        """        pass


    def setPlaybackBy(self, *args, **kwargs):        """        setPlaybackBy(float) -> None                Specify the increment between times viewed during the playing of the animation.        """        pass


    def setPlaybackMode(self, *args, **kwargs):        """        setPlaybackMode(int) -> None                Set the current playback mode.        """        pass


    def setPlaybackSpeed(self, *args, **kwargs):        """        setPlaybackSpeed(float) -> None                Set the desired speed factor at which the animation will play back.        """        pass


    def setViewMode(self, *args, **kwargs):        """        setViewMode(int) -> None                Set the current viewing mode.        Controls whether the animation is run in only the active view, or simultaneously in all views.        """        pass


    def setWeightedTangents(self, *args, **kwargs):        """        setWeightedTangents(bool) -> None                Sets whether or not the tangents on the Anim Curve are weighted.        """        pass


    def stop(self, *args, **kwargs):        """        stop() -> None                Stop playing the current animation.        """        pass


    def viewMode(self, *args, **kwargs):        """        viewMode() -> int                Return the viewing mode currently in effect:          MAnimControl.kPlaybackViewAll      Playback in all views.          MAnimControl.kPlaybackViewActive   Playback in only the active view.        """        pass


    def weightedTangents(self, *args, **kwargs):        """        weightedTangents() -> bool                Determine whether or not the tangents on the Anim Curve are weighted.        """        pass


