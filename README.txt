在github上，机制实现代码都保存在 Branches main(default) 这个分支当中，而生成的实验数据和实验结果保存在 Branches master 中，
请自行切换 github 中的 Branches 选项再进行下载。

建议将 Branches main(default) 中 所有的解决方案文件夹（实验代码）和 Branches master 的 data 文件夹都存放在同一个自定义文件夹中，即
自定义的文件夹下应当包含 ：
（1）文件夹：1GenerateData, 
（2）文件夹：2RandomSampling, 
（3）文件夹：3OPT_TRAP, 
（4）文件夹：4OVMAP_mod, 
（5）文件夹：5OTRAP, 
（6）文件夹：6TruthfulnessVerification 
（7）文件夹 ：data

文件夹：1GenerateData, 2RandomSampling, 3OPT_TRAP, 4OVMAP_mod, 5OTRAP 和 6TruthfulnessVerification 存放 VS 的C++解决方案，即论文实验代码

按照实验顺序，各解决方案的功能如下：
1. 1GenerateData 生成实验用的大数据库，并保存到本地。
2. 2RandomSampling 读入 1GenerateData 生成的大数据库中的ECS和车辆信息，进行“随机抽取”工作，并保存到本地。
3. 3OPT_TRAP, 4OVMAP_mod, 5OTRAP 分别读入 2RandomSampling 抽取的相同数据，进行实验，并把实验结果保存到本地。

文件夹：data 中存放了各个解决方案生成的实验数据，以及实验结果。例如：
1. （1）文件夹 data\1GenerateData\exp1_exp2 存放 6.2.1 小节 和 6.2.2 小节 使用的大数据库（已压缩）
    （2）文件夹 data\1GenerateData\exp3 存放 6.2.3 小节使用的大数据库（已压缩）
    （3）文件夹 data\1GenerateData\old 存放旧实验生成的大数据库（不带投标系数）
      NOTE：
          ① 6.2.1 和 6.2.2 小节 的实验环境都是 10个小型ECS，所以这两节的实验数据库可以一起生成
          ② 6.2.3 小节中，当ECS类型不一样时，ECS的信号覆盖范围也不会不一样，就导致车辆的部署矩阵会发生变化，所以 6.2.3 小节的实验数据需要重新生成
2. （1）文件夹 data\2RandomSampling\exp1 存放 6.2.1 小节实验中读入的数据（已抽取）
    （2）文件夹 data\2RandomSampling\exp2 存放 6.2.2 小节实验中读入的数据（已抽取）
    （3）文件夹 data\2RandomSampling\exp3 存放 6.2.3 小节实验中读入的数据（已抽取）
    （4）文件夹 data\ExperimentalResult\exp3_add_SW\data 存放 6.2.3 小节实验中，不带投标系数的是实验数据（有12000个数据，只读入10000个），实验结果如论文中图16所示。
    （5）文件夹 data\ExperimentalResult\exp4_TruthfulnessVerification\TruthfulnessVerification_data（压缩包）存放 6.2.4 小节实验读入的数据
      NOTE：
          ① 6.2.1 小节：车辆任务请求=10000 的实验；6.2.2 小节：大型车辆任务请求比例=0% 的实验；
              6.2.3小节：ECS类型为：S_M_L = 10_0_0 的实验；6.2.4 小节的真实性验证实验，这 4 个实验使用的读入数据都是一样的。
          ② 6.2.3小节，不带投标系数的实验的读入数据来源于以前生成的 实验数据（不带投标系数），其保存路径为 data\2RandomSampling\old\data_RS_CarInfo_12000_12000_12000.rar

3. 格式说明：以随机抽取的实验一（6.2.1小节实验）的数据为例（路径为\data\2RandomSampling\exp1）：
    （1）所有带前缀“data_”的 .txt 文件都用作算法读入，如“data_RS_CarInfo_10000_0_0-1.txt”.
            不带前缀“data_”的 .txt 文件可供读者查看生成的数据信息，如“RS_CarInfo_10000_0_0-1.txt”.
    （2）文件名介绍，例如：①“EcsInfo_10_0_0.txt”，②“RS_CarInfo_10000_0_0-1.txt”，③“data_RS_Car_CM_S_10000-1.txt”
            ① EcsInfo_ 表示这是基站(ECS)信息数据，
                10_0_0 = S_M_L 表示本实验中的基站有 10 个小型基站，0 个中型基站 和 0个 大型基站，
                并且，同文件夹下的其他车辆信息文件（特指时变部署约束矩阵）也都是基于 10 个小型基站信息（尤其是信号覆盖范围）来生成的。
                那么，EcsInfo_10_0_0.txt 就是：生成的“供用户查看的”基站信息数据，其中，包含 10 个小型基站，0 个中型基站 和 0个 大型基站 的信息
            ② RS_ = RandomSampling，表示数据已经过项目 2Randomsampling 的随机抽取；
                CarInfo_ 表示这是车辆信息数据，
                10000_0_0  = S_M_L 表示该文件中含有 10000个小型车辆任务请求信息，0个中型车辆任务请求信息，0个大型车辆任务请求信息
                -1 表示这是第 1 次随机抽取的 车辆信息。
                那么，RS_CarInfo_10000_0_0-1.txt 就是：“第 1 次随机抽取”的“供用户查看”的车辆信息数据，其中，包含 10000个小型车辆任务请求信息，0个中型车辆任务请求信息和 0个大型车辆任务请求信息
            ③ 车辆的部署约束矩阵（又称可连接矩阵）需要单独存放，而且，因为数据量过大，无法正常打开查看（文件中只包含 0 或 1 ）。
                data_ : 表示这是供算法输入使用（用户无法查看）
                RS_ = RandomSampling，表示数据已经过项目 2Randomsampling 的随机抽取；
                Car_ : 表示这是车辆数据
                CM_ : 这是可连接矩阵(Connectable Matrix)的缩写，等价于时变部署约束矩阵
                S_10000 = Small_10000 : 表示该文件中是 10000 个小型车辆任务请求的时变部署约束矩阵
                -1 ：这是 第 1 次 随机抽取的车辆信息的时变部署约束矩阵（可连接矩阵）
                那么，data_RS_Car_CM_S_10000-1.txt 就是：“第 1 次随机抽取”的“供算法输入使用”的 10000 个 小型 车辆任务请求的 时变部署约束矩阵，

4.（1）文件夹 data\ExperimentalResult\exp1 存放 6.2.1 小节实验的实验结果并附有 EXCEL 表以统计实验结果
   （2）文件夹 data\ExperimentalResult\exp2 存放 6.2.2 小节实验的实验结果并附有 EXCEL 表以统计实验结果
   （3）文件夹 data\ExperimentalResult\exp3 存放 6.2.3 小节实验的实验结果并附有 EXCEL 表以统计实验结果
   （4）文件夹 data\ExperimentalResult\exp3_add_SW 存放 6.2.3 小节实验中 不带投标系数的实验结果（社会福利）并附有 EXCEL 表以统计实验结果
   （5）文件夹 data\ExperimentalResult\exp4_TruthfulnessVerification 存放 6.2.4 小节的真实性验证实验的实验结果（胜者25270 和 败者35835）并附有 EXCEL 表以统计实验结果
     NOTE：
          ① 举例：OPT_TRAP_Solution_CarInfo_100_0_0-1.txt
              OPT_TRAP_Solution : 表示这是 OPT_TRAP 机制的求解结果
              CarInfo_100_0_0 : 表示本次输入的车辆信息为：100个小型车辆任务请求，0个中型车辆任务请求 和 0 个大型车辆任务请求
              -1 : 表示这是第 1 次 随机抽取的车辆信息作为输入 而 得出的求解方案
              那么，OPT_TRAP_Solution_CarInfo_100_0_0-1.txt 就是：OPT_TRAP 机制以“第 1 次随机抽取的 100个小型车辆任务请求信息”作为输入，得到的求解方案
          ② OVMAP_mod_Solution_CarInfo_100_0_0-1.txt 就是：OVMAP* 机制以“第 1 次随机抽取的 100个小型车辆任务请求信息”作为输入，得到的求解方案
          ③ OTRAP_Solution_CarInfo_100_0_0-1.txt 就是：OTRAP 机制以“第 1 次随机抽取的 100个小型车辆任务请求信息”作为输入，得到的求解方案

如果需要查看论文，可登陆云南大学图书馆，查看硕士论文《车联网边缘计算环境下具有时变约束的在线拍卖机制设计》的第四章内容。

                
                
      
          
