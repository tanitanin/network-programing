
// This file is auto-generated from test.idl
// *** DO NOT EDIT ***
<?php

include_once 'Net/MessagePackRPC.php';



class ObjectDecoder {
  public static $USER_DEFINED_CLASSES = array(
    
  );
  public static function decodeToObject($ret_array, $type_array) {
    if ($type_array == "") {
      // do nothing
      $ret = $ret_array;
    } else if (in_array($type_array, self::$USER_DEFINED_CLASSES)) {
      // array -> object
      $ret = new $type_array();
      $ret_keys = array_keys((array)$ret);
      for ($i = 0; $i < count($ret_keys); $i++) {
        $ret->{$ret_keys[$i]} = $ret_array[$i];
      }
    } else {
      // dissolve array
      if (is_array($type_array)) {
        if (count($type_array) == 1) {
          // if array
          foreach ($type_array as $key => $type) {
            foreach ($ret_array as $ret_key => $ret_value) {
              $ret[$ret_key] = $this->decodeToObject($ret_value, $type);
            }
          }
        } else {
          // if tuple
          $ret = array();
          $i = 0;
          foreach ($type_array as $type) {
            $ret[$i] = $this->decodeToObject($ret_array[$i], $type);
            $i++;
          }
        }
      } else {
        // type error
        return $ret_array;
      }
    }
    return $ret;
  }
}
 

?>
