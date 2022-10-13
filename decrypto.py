

TITLE = "Agojyxyfakafoq risetefoxaxuhe besalufavyqabefu idojatejolup ebizuvekukef cihite"

TXT = '''Yhakukyzyp sohaqyzaso ganixozynucopy xatubiqoma dehoqicaze ijokuqycaxejot ydub nytebi xyvuqakawatusudy bunyve ebepux pagejimavixu iw buzicosinati uvodylybiqemim ozotyjowigymyqas ukapep eqowyp iduvif byhino. Hekusydysika ox yqesywumoh giluripu zi ynahosah odyracycovuw zykajetige doly didamohisudaha pe hibilu arydudykuzyl adybibaqukinuj op cy cizacixogawesugi nu ydit itewisewapuf nymanirolo edigypar.
Opim ykomocox ibevebifiwemeb huriry iloboxyfamiras hapesedevy adiruholoj abax mypafigolezo sedalenidi ruro kevovufe ur gyqehegitiwe cugamofutitobeve egyhaw ulaxocejyx dawywojolomiwu ig upydezaj ofytimoxiq.
Ecokabozajudez iqyh daralexazyza te sevomasuxorivi otyxigyf ucybeqequsan amiv yxokehyp apynides iziputekuqoj okedywobopeh gakibusonupugu iqosinexihyt odyjep kurilugocypygo soxuxiletevy tygi umuj bivinipehimuse hilo.
Ijakumolezadyg ripuwulybo ykimocuj yfugevyquw bufilivo adabobud ujip jidygedywo lamafociresymuki aputatywucutol irikonyzur eqihiseqaxidyluj tukacyti pydefekykazihidu yfagoryd umeqepipyhiqyzim idizutep ynywetavuw qa ovaceqilohetov akahuhinobihylev xabisusawi pofywu ty. Dybyjafedymydy qecilunynifo okeduf tohuqegugozo rego elemyw ux lodekaryhawigi itytibazozifif ylorejipevevun egylajulytydug qeniju vixalesewehoce wuqixilyhureca zofuci otuhepedofes iq oloqofamowex labimityrehihu ocajasuxyp apelacukuxixevet ixaxecapejisyx eqez ilijidejatitaroh.'''



class MNode:
    def __init__(self):
        self.mapped = {}


nodes = [] # per word count

HISTOGRAM = {}

def parse():
    data = TXT.split(' ')
    print(len(data))
    for d in data:
        if len(d) % 2 == 0:
            i, j = 0, 2
            node = MNode()
            while i < len(d):
                slice = d[i:j]
                if slice not in node.mapped:
                    node.mapped.update({slice :  1})                    
                else:
                    node.mapped[slice] += 1 

                if slice not in HISTOGRAM:
                    HISTOGRAM.update({slice :  1})
                else:
                    HISTOGRAM[slice] += 1 
                i+=2
                j+=2
            nodes.append(node)
            pass 



if __name__ == "__main__":
    parse()
    for n in nodes:
        print(n.mapped)
    print("####################################")
    print(HISTOGRAM)
    pass