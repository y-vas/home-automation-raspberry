<?php
use Mark\App;

require dirname(__DIR__) . '/vendor/autoload.php';

$api = new App('http://0.0.0.0:3000' );
$api->count = 4;

$api->any('/', function ( $requst ){
  return 'Hello world';
});

// $api->get('/light/{id}/{status}', function( $requst, $key , $status ){
//   return exec("cd ../app && python3 lights.py $key $status");
// });

$api->post('/user/create', function ( $requst ){

  return json_encode([
      'code'    => 0   ,
      'message' => 'ok'
  ]);
});

$api->start();
