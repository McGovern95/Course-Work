insert into player values ('11111','kylerulez121','Kyle playerson','$assword','1990-05-20', 
                           '1223 Laglign drive','roper@gmail.com','5754433433',
                           'small forward');
insert into player values ('11112', 'mjgoat23', 'Michael Jordan', 'goat23', '1989-07-23', 
                           '2345 Laney drive', 'goat23@yahoo.com', '5751235555', 
                           'shooting guard');
insert into player values ('11113', 'emj32', 'Magic Johnson', 'lakerz32', '1991-01-1', 
                           '2345 Michagin st', 'mj32@gmail.com', '5750050055', 
                           'point guard');                          
insert into player values ('11114', 'timmy21', 'Tim Duncan', 'spurs21', '1990-09-15', 
                           '0021 San Spurs ave', '5rings@yahoo.com', '5751659988', 
                           'power forward');
insert into player values ('11115', 'gasol16', 'Pau Gasol', 'la16', '1990-02-24', 
                           '5421 Espana drive', 'pau16@yahoo.com', '5056529985', 
                           'center');
                           
insert into manager values ('23232','teacherson111','robert teacherson','1234','1960-04-20',
                            '121 ingloo st','yulostt3@gmail.com','5753233331');
insert into manager values ('23233','jackson11','Phil Jackson','jack11','1961-11-04',
                            '898 Champion st','11rings@gmail.com','5755556645');
insert into manager values ('23234','riley5','Pat Riley','riley305','1965-12-25',
                            '305 Florida st','r_05@hotmail.com','5755652789');
insert into manager values ('23235','g_spurs','Gregg Popovich','pop05','1959-05-23',
                            '1014 Alamo st','spursman@gmail.com','5756479852');
insert into manager values ('23236','walton2','Luke Walton','lalukey','1979-6-27',
                            '652 South Bay drive','lawal@hotmail.com','5755686585');
 
insert into staff values ('32231','Yugloo Staffer','1988-04-20','11 Niost ct', 
                          'tinman@gmail.com','5756666666','coffee boy');
insert into staff values ('32232','Jon Snow','1986-10-31','119 Winterfell St.', 
                          'snowStark@yahoo.com','5758888888','ball boy');                          
insert into staff values ('32233','Bran Stark','1992-11-30','002 Winterfell St.', 
                          'summer06@yahoo.com','5753338568','floor boy');
insert into staff values ('32234','Bobby Boucher','1992-11-22','520 Spooner St.', 
                          'ilovemomma@gmail.com','5753325856','water boy');                          
insert into staff values ('32235','Podrick Payne','1993-08-31','156 Red Keep St.', 
                          'goatsquire@yahoo.com','5757775556','towel boy');	

insert into managercertificate values ('23232','90901', '00000');
insert into managercertificate values ('23233','90201', '00001');				
insert into managercertificate values ('23234','90202', '00002');
insert into managercertificate values ('23235','90203', '00003');
insert into managercertificate values ('23236','90204', '00004');

insert into stats values ('11111', '2016', '10', '1' );
insert into stats values ('11112', '2016', '30', '6' );
insert into stats values ('11113', '2016', '22', '12' );
insert into stats values ('11114', '2016', '18', '4' );
insert into stats values ('11115', '2016', '16', '3' );

insert into training values ('lifting','get stronger','30');
insert into training values ('shooting','practice three point shot','30');
insert into training values ('dribbling','keeping eyes up when dribbling','24');
insert into training values ('post','practice post moves','36');
insert into training values ('defense','practice post defense','20');

insert into assigntraining values ('11111','23232','lifting');
insert into assigntraining values ('11112','23233','shooting');
insert into assigntraining values ('11113','23234','dribbling');
insert into assigntraining values ('11114','23235','post');
insert into assigntraining values ('11115','23236','defense');

insert into game values ('66','2016-08-10','Lose','The Venue','The Tunnel Snakes');
insert into game values ('67','2016-08-13','Win','Staples Center','Jazz');
insert into game values ('68','2016-08-15','Win','TD Garden','Celtics');
insert into game values ('69','2016-08-20','lose','Oracle Arena','Warriors');
insert into game values ('70','2016-08-22','Tie','Madison Square Garden','Knicks');

insert into play values ('11111', '66');
insert into play values ('11112', '67');
insert into play values ('11113', '68');
insert into play values ('11114', '69');
insert into play values ('11115', '70');

commit;
