# generated from rosidl_generator_py/resource/_idl.py.em
# with input from auto_aim_interfaces:msg/Gimbal.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Gimbal(type):
    """Metaclass of message 'Gimbal'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('auto_aim_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'auto_aim_interfaces.msg.Gimbal')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__gimbal
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__gimbal
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__gimbal
            cls._TYPE_SUPPORT = module.type_support_msg__msg__gimbal
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__gimbal

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Gimbal(metaclass=Metaclass_Gimbal):
    """Message class 'Gimbal'."""

    __slots__ = [
        '_header',
        '_pitch',
        '_yaw',
        '_distance',
        '_is_switched',
        '_is_target',
        '_is_spinning',
        '_is_spinning_switched',
        '_is_shooting',
        '_is_prediction',
        '_meas_point_cam',
        '_pred_point_cam',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'pitch': 'float',
        'yaw': 'float',
        'distance': 'float',
        'is_switched': 'boolean',
        'is_target': 'boolean',
        'is_spinning': 'boolean',
        'is_spinning_switched': 'boolean',
        'is_shooting': 'boolean',
        'is_prediction': 'boolean',
        'meas_point_cam': 'geometry_msgs/Point',
        'pred_point_cam': 'geometry_msgs/Point',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.pitch = kwargs.get('pitch', float())
        self.yaw = kwargs.get('yaw', float())
        self.distance = kwargs.get('distance', float())
        self.is_switched = kwargs.get('is_switched', bool())
        self.is_target = kwargs.get('is_target', bool())
        self.is_spinning = kwargs.get('is_spinning', bool())
        self.is_spinning_switched = kwargs.get('is_spinning_switched', bool())
        self.is_shooting = kwargs.get('is_shooting', bool())
        self.is_prediction = kwargs.get('is_prediction', bool())
        from geometry_msgs.msg import Point
        self.meas_point_cam = kwargs.get('meas_point_cam', Point())
        from geometry_msgs.msg import Point
        self.pred_point_cam = kwargs.get('pred_point_cam', Point())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.pitch != other.pitch:
            return False
        if self.yaw != other.yaw:
            return False
        if self.distance != other.distance:
            return False
        if self.is_switched != other.is_switched:
            return False
        if self.is_target != other.is_target:
            return False
        if self.is_spinning != other.is_spinning:
            return False
        if self.is_spinning_switched != other.is_spinning_switched:
            return False
        if self.is_shooting != other.is_shooting:
            return False
        if self.is_prediction != other.is_prediction:
            return False
        if self.meas_point_cam != other.meas_point_cam:
            return False
        if self.pred_point_cam != other.pred_point_cam:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if __debug__:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @property
    def pitch(self):
        """Message field 'pitch'."""
        return self._pitch

    @pitch.setter
    def pitch(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pitch' field must be of type 'float'"
        self._pitch = value

    @property
    def yaw(self):
        """Message field 'yaw'."""
        return self._yaw

    @yaw.setter
    def yaw(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw' field must be of type 'float'"
        self._yaw = value

    @property
    def distance(self):
        """Message field 'distance'."""
        return self._distance

    @distance.setter
    def distance(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'distance' field must be of type 'float'"
        self._distance = value

    @property
    def is_switched(self):
        """Message field 'is_switched'."""
        return self._is_switched

    @is_switched.setter
    def is_switched(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_switched' field must be of type 'bool'"
        self._is_switched = value

    @property
    def is_target(self):
        """Message field 'is_target'."""
        return self._is_target

    @is_target.setter
    def is_target(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_target' field must be of type 'bool'"
        self._is_target = value

    @property
    def is_spinning(self):
        """Message field 'is_spinning'."""
        return self._is_spinning

    @is_spinning.setter
    def is_spinning(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_spinning' field must be of type 'bool'"
        self._is_spinning = value

    @property
    def is_spinning_switched(self):
        """Message field 'is_spinning_switched'."""
        return self._is_spinning_switched

    @is_spinning_switched.setter
    def is_spinning_switched(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_spinning_switched' field must be of type 'bool'"
        self._is_spinning_switched = value

    @property
    def is_shooting(self):
        """Message field 'is_shooting'."""
        return self._is_shooting

    @is_shooting.setter
    def is_shooting(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_shooting' field must be of type 'bool'"
        self._is_shooting = value

    @property
    def is_prediction(self):
        """Message field 'is_prediction'."""
        return self._is_prediction

    @is_prediction.setter
    def is_prediction(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_prediction' field must be of type 'bool'"
        self._is_prediction = value

    @property
    def meas_point_cam(self):
        """Message field 'meas_point_cam'."""
        return self._meas_point_cam

    @meas_point_cam.setter
    def meas_point_cam(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'meas_point_cam' field must be a sub message of type 'Point'"
        self._meas_point_cam = value

    @property
    def pred_point_cam(self):
        """Message field 'pred_point_cam'."""
        return self._pred_point_cam

    @pred_point_cam.setter
    def pred_point_cam(self, value):
        if __debug__:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'pred_point_cam' field must be a sub message of type 'Point'"
        self._pred_point_cam = value
