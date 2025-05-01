# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ig_lio_c_msgs:srv/CovertMap.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_CovertMap_Request(type):
    """Metaclass of message 'CovertMap_Request'."""

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
            module = import_type_support('ig_lio_c_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ig_lio_c_msgs.srv.CovertMap_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__covert_map__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__covert_map__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__covert_map__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__covert_map__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__covert_map__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class CovertMap_Request(metaclass=Metaclass_CovertMap_Request):
    """Message class 'CovertMap_Request'."""

    __slots__ = [
        '_pcd_path',
        '_map_file_name',
        '_image_format',
        '_map_mode',
        '_free_thresh',
        '_occupied_thresh',
    ]

    _fields_and_field_types = {
        'pcd_path': 'string',
        'map_file_name': 'string',
        'image_format': 'string',
        'map_mode': 'string',
        'free_thresh': 'float',
        'occupied_thresh': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.pcd_path = kwargs.get('pcd_path', str())
        self.map_file_name = kwargs.get('map_file_name', str())
        self.image_format = kwargs.get('image_format', str())
        self.map_mode = kwargs.get('map_mode', str())
        self.free_thresh = kwargs.get('free_thresh', float())
        self.occupied_thresh = kwargs.get('occupied_thresh', float())

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
        if self.pcd_path != other.pcd_path:
            return False
        if self.map_file_name != other.map_file_name:
            return False
        if self.image_format != other.image_format:
            return False
        if self.map_mode != other.map_mode:
            return False
        if self.free_thresh != other.free_thresh:
            return False
        if self.occupied_thresh != other.occupied_thresh:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def pcd_path(self):
        """Message field 'pcd_path'."""
        return self._pcd_path

    @pcd_path.setter
    def pcd_path(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'pcd_path' field must be of type 'str'"
        self._pcd_path = value

    @property
    def map_file_name(self):
        """Message field 'map_file_name'."""
        return self._map_file_name

    @map_file_name.setter
    def map_file_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_file_name' field must be of type 'str'"
        self._map_file_name = value

    @property
    def image_format(self):
        """Message field 'image_format'."""
        return self._image_format

    @image_format.setter
    def image_format(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'image_format' field must be of type 'str'"
        self._image_format = value

    @property
    def map_mode(self):
        """Message field 'map_mode'."""
        return self._map_mode

    @map_mode.setter
    def map_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'map_mode' field must be of type 'str'"
        self._map_mode = value

    @property
    def free_thresh(self):
        """Message field 'free_thresh'."""
        return self._free_thresh

    @free_thresh.setter
    def free_thresh(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'free_thresh' field must be of type 'float'"
        self._free_thresh = value

    @property
    def occupied_thresh(self):
        """Message field 'occupied_thresh'."""
        return self._occupied_thresh

    @occupied_thresh.setter
    def occupied_thresh(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'occupied_thresh' field must be of type 'float'"
        self._occupied_thresh = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_CovertMap_Response(type):
    """Metaclass of message 'CovertMap_Response'."""

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
            module = import_type_support('ig_lio_c_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ig_lio_c_msgs.srv.CovertMap_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__covert_map__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__covert_map__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__covert_map__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__covert_map__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__covert_map__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class CovertMap_Response(metaclass=Metaclass_CovertMap_Response):
    """Message class 'CovertMap_Response'."""

    __slots__ = [
        '_status',
        '_message',
    ]

    _fields_and_field_types = {
        'status': 'int32',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.status = kwargs.get('status', int())
        self.message = kwargs.get('message', str())

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
        if self.status != other.status:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= -2147483648 and value < 2147483648, \
                "The 'status' field must be an integer in [-2147483648, 2147483647]"
        self._status = value

    @property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


class Metaclass_CovertMap(type):
    """Metaclass of service 'CovertMap'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('ig_lio_c_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ig_lio_c_msgs.srv.CovertMap')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__covert_map

            from ig_lio_c_msgs.srv import _covert_map
            if _covert_map.Metaclass_CovertMap_Request._TYPE_SUPPORT is None:
                _covert_map.Metaclass_CovertMap_Request.__import_type_support__()
            if _covert_map.Metaclass_CovertMap_Response._TYPE_SUPPORT is None:
                _covert_map.Metaclass_CovertMap_Response.__import_type_support__()


class CovertMap(metaclass=Metaclass_CovertMap):
    from ig_lio_c_msgs.srv._covert_map import CovertMap_Request as Request
    from ig_lio_c_msgs.srv._covert_map import CovertMap_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
