var TEST_MODEL_URL = 'http://hifi-content.s3.amazonaws.com/james/avatars/Jack_Skellington/Jack_Skellington.fbx';

var doppelgangers = [];

function Doppelganger(avatar) {
    this.initialProperties = {
        name: 'Hifi-Doppelganger',
        type: 'Model',
        modelURL: TEST_MODEL_URL,
       // dimensions: getAvatarDimensions(avatar),
        position: putDoppelgangerAcrossFromAvatar(this, avatar),
        rotation: rotateDoppelgangerTowardAvatar(this, avatar),
    };

    this.id = createDoppelgangerEntity(this);
    this.avatar = avatar;
    return this;
}

function getJointData(avatar) {
    var allJointData;
    var jointNames = MyAvatar.jointNames;

    jointNames.forEach(function(joint) {
        print('getting info for joint:' + joint);
        var jointData = MyAvatar.getJointPosition(joint);
        print('joint data:'+JSON.stringify(jointData));
    });

    return allJointData;
}

function setJointData(doppelganger, jointData) {
    return true;
}

function mirrorJointData() {
    return mirroredJointData;
}

function createDoppelganger(avatar) {
    return new Doppelganger(avatar);
}

function createDoppelgangerEntity(doppelganger) {
    return Entities.addEntity(doppelganger.initialProperties);
}

function putDoppelgangerAcrossFromAvatar(doppelganger, avatar) {
    var avatarRot = Quat.fromPitchYawRollDegrees(0, avatar.bodyYaw, 0.0);
    var basePosition = Vec3.sum(avatar.position, Vec3.multiply(1.5, Quat.getFront(avatarRot)));
    return basePosition;
}

function getAvatarDimensions(avatar) {
    return dimensions;
}

function rotateDoppelgangerTowardAvatar(doppelganger, avatar) {
       var avatarRot = Quat.fromPitchYawRollDegrees(0, avatar.bodyYaw, 0.0);
       avatarRot = Vec3.multiply(-1,avatarRot);
    return avatarRot;
}

function connectDoppelgangerUpdates() {
    Script.update.connect(updateDoppelganger);
}

function disconnectDoppelgangerUpdates() {
    Script.update.disconnect(updateDoppelganger);
}

function updateDoppelganger() {
    doppelgangers.forEach(function(doppelganger) {
        var joints = getJointData(MyAvatar);
        var mirroredJoints = mirrorJointData(joints);
        setJointData(doppelganger, mirroredJoints);
    });

}

function makeDoppelgangerForMyAvatar() {
    var doppelganger = createDoppelganger(MyAvatar);
    doppelgangers.push(doppelganger);
   // connectDoppelgangerUpdates();
}


makeDoppelgangerForMyAvatar();

function cleanup() {
    disconnectDoppelgangerUpdates();

    doppelgangers.forEach(function(doppelganger) {
        Entities.deleteEntity(doppelganger);
    });

}

Script.scriptEnding.connect(cleanup);

//  APPEND_ENTITY_PROPERTY(PROP_JOINT_ROTATIONS_SET, getJointRotationsSet());
// APPEND_ENTITY_PROPERTY(PROP_JOINT_ROTATIONS, getJointRotations());
//  APPEND_ENTITY_PROPERTY(PROP_JOINT_TRANSLATIONS_SET, getJointTranslationsSet());
// APPEND_ENTITY_PROPERTY(PROP_JOINT_TRANSLATIONS, getJointTranslations());