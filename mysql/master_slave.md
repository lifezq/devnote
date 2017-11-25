
## 1 . Master server config   
>  [server]   
>  server_id=1   
>  log_bin=mysql-bin   
>     
>  innodb_buffer_pool_size = 4G   
>  innodb_log_buffer_size = 16M   
>  innodb_flush_log_at_trx_commit = 2    

### mysql-cli    
>  grant replication slave,reload,super on *.* to 'backup'@'s02' identified by 'pass_string' with grant option;
> - (Only data from host s02 is allowed here)

### export data
>   mysqldump -u root -p'pass_string' -a --databases db01 db02 > backup.sql

## 2 . Slave server config    
>  [server]    
>  server_id=2    
>  log_bin=mysql-bin    
>  relay_log=mysql-relay-bin    
>  log_slave_updates=1   
>  read_only=1    
>      
>  innodb_buffer_pool_size = 4G  
>  innodb_log_buffer_size = 16M   
>  innodb_flush_log_at_trx_commit = 2   


### slave mysql-cli
change master to master_host='s01', master_user='backup', master_password='pass_string', master_log_file='mysql-bin.000001',master_log_pos=0;

>   show slave status\G    
>   start slave;   
>   show slave status\G   
>   show processlist \G   


### import data   
>  mysql -uroot -p'pass_string' < backup.sql   

