
<?php
include_once(dirname(__FILE__)."/test_types.php");


class hoge {
  public function __construct($host, $port) {
    $this->client = new MessagePackRPC_Client($host, $port);
  }

  public function get($key) {
    $ret = $this->client->call("get", array($key));
    $type_array = "";
    return ObjectDecoder::decodeToObject($ret, $type_array);
  }

  public function set($key, $val) {
    $ret = $this->client->call("set", array($key, $val));
    $type_array = "";
    return ObjectDecoder::decodeToObject($ret, $type_array);
  }

  private $client;
}

?>
